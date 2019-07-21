#include <stdint.h>
#include <string.h>
#include "my_sbrk.h"
#include "my_malloc.h"

#define SBRK_SIZE 2048
#define WORD_SIZE 8
#define TOTAL_METADATA_SIZE ((sizeof(metadata_t) + sizeof(long)) / WORD_SIZE)
#define MIN_BLOCK_SIZE (TOTAL_METADATA_SIZE + 1)

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you may receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf(x)
#else
#define DEBUG_PRINT(x)
#endif

metadata_t* freelist;

static void updateBlock(metadata_t* block, metadata_t* next, unsigned long size);
static void addNode(metadata_t* block);
static void removeNode(metadata_t* block);
static void splitBlock(metadata_t* block, unsigned long size);
static void joinBlocks(metadata_t* a, metadata_t* b);
static void* findBestFit(unsigned long size);

// MALLOC
void* my_malloc(size_t size) {
  if (size == 0) {
    ERRNO = NO_ERROR;
    return NULL;
  }
  // Calculate the total size needed in terms of words
  if (size % WORD_SIZE != 0) {
    size = size + (WORD_SIZE - size % WORD_SIZE);
  }
  unsigned long total_size = TOTAL_METADATA_SIZE + size / WORD_SIZE;
  // Search for available space
  if (total_size * WORD_SIZE > SBRK_SIZE) {
    ERRNO = SINGLE_REQUEST_TOO_LARGE;
    return NULL;
  }
  metadata_t* temp = findBestFit(total_size);
  if (!temp) {
    // Call my_sbrk if there is not enough space
    metadata_t* new_block = my_sbrk(SBRK_SIZE);
    if (new_block == NULL) {
      ERRNO = OUT_OF_MEMORY;
      return NULL;
    }
    // Update the new block and freelist
    updateBlock(new_block, NULL, SBRK_SIZE/WORD_SIZE);
    addNode(new_block);
    temp = findBestFit(total_size);
  }
  ERRNO = NO_ERROR;
  return temp + 1;
}

static void* findBestFit(unsigned long size) {
  metadata_t* cur = freelist;
  metadata_t* best = NULL;
  metadata_t* backup = NULL;
  while (cur != NULL) {
    // Return immediately if exact fit is found.
    if (cur->size == size) {
      removeNode(cur);
      return cur;
    }
    if (cur->size >= size) {
      if ((cur->size - size >= MIN_BLOCK_SIZE)
        && (!best || cur->size < best->size)) {
        best = cur;
      } else if (!backup || cur->size < backup->size) {
        backup = cur;
      }
    }
    cur = cur->next;
  }
  // Allocate a new block if the best fit is found
  if (best != NULL) {
    splitBlock(best, size);
    ERRNO = NO_ERROR;
    return best;
  }
  // Return any of the blocks that is large enough if the best fit is not found.
  if (backup != NULL) {
    removeNode(backup);
    ERRNO = NO_ERROR;
    return backup;
  }
  return best;
}

// REALLOC
void* my_realloc(void* ptr, size_t size) {
  if (ptr == NULL) {
    return my_malloc(size);
  } else {
    if (size == 0) {
      my_free(ptr);
      return NULL;
    }
    // Reallocate
    void* new_ptr = my_malloc(size);
    if (!new_ptr) {
      return NULL;
    }
    metadata_t* block = (metadata_t*)((char*)ptr - sizeof(metadata_t));
    size_t oldsize = (size_t) (block->size - TOTAL_METADATA_SIZE) * WORD_SIZE;
    // The number of bytes that needs to be copied
    size_t n;
    if (size < oldsize) {
      n = size;
    } else {
      n = oldsize;
    }
    memcpy(new_ptr, ptr, n);
    my_free(ptr);
    return new_ptr;
  }
}

// CALLOC
void* my_calloc(size_t nmemb, size_t size) {
  void* temp = my_malloc(nmemb * size);
  for (int i = 0; i < nmemb*size; i++) {
    ((char*)temp)[i] = 0;
  }
  return temp;
}

// FREE
void my_free(void* ptr) {
  metadata_t* block = (metadata_t*)ptr - 1;
  if (block->canary != ((uintptr_t)block ^ block->size)) {
    ERRNO = CANARY_CORRUPTED;
    return;
  }
  unsigned long footer_canary =
    *((unsigned long*)((char*)block + block->size * WORD_SIZE - sizeof(long)));
  if (block->canary != footer_canary) {
    ERRNO = CANARY_CORRUPTED;
    return;
  }
  addNode(block);
  ERRNO = NO_ERROR;
  return;
}


// Helper method that updates the metadata and canaries of a block.
static void updateBlock(metadata_t* block, metadata_t* next, unsigned long size) {
  block->next = next;
  block->size = size;
  block->canary = (uintptr_t)block ^ block->size;
  *((unsigned long*)((char*)block + size*WORD_SIZE - sizeof(long))) = block->canary;
}

/* Helper method that splits a large enough block into two blocks,
 * updates the canaries of both blocks, removes the old block from
 * freelist and adds the new block on the right to freelist.
 */
static void splitBlock(metadata_t* block, unsigned long size) {
  metadata_t* new_block = (metadata_t*)((char*)block + size*WORD_SIZE);
  updateBlock(new_block, block->next, block->size-size);
  updateBlock(block, NULL, size);
  removeNode(block);
  addNode(new_block);
}

/* Helper method that inserts the first block in front of the
 * second in the freelist and merge them if they are adjacent.
 */
static void joinBlocks(metadata_t* a, metadata_t* b) {
  if ((char*)a + a->size*WORD_SIZE == (char*)b) {
    updateBlock(a, b->next, a->size + b->size);
  } else {
    a->next = b;
  }
}

// Helper method that adds a free block to the freelist
static void addNode(metadata_t* block) {
  if (freelist == NULL) {
    freelist = block;
  } else if ((uintptr_t)block < (uintptr_t)freelist) {
    joinBlocks(block, freelist);
    freelist = block;
  } else {
    metadata_t* cur = freelist;
    while (cur->next != NULL
      && (uintptr_t)cur->next < (uintptr_t)block) {
      cur = cur->next;
    }
    if (cur->next != NULL) {
      joinBlocks(block, cur->next);
    }
    joinBlocks(cur, block);
  }
}

// Helper method that removes a node from the freelist
static void removeNode(metadata_t* block) {
  if (freelist == NULL) {
    return;
  } else if (freelist == block) {
    freelist = freelist->next;
  } else {
    metadata_t* cur = freelist;
    while (cur-> next != NULL && cur->next != block) {
      cur = cur->next;
    }
    if (cur->next == NULL) {
      return;
    }
    cur->next = cur->next->next;
  }
}
