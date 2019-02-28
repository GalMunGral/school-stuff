#include "cachesim.h"

#define TRUE 1
#define FALSE 0

typedef struct block {
  uint64_t tag;  // The tag stored in that block
  uint8_t valid; // Valid bit
  uint8_t dirty; // Dirty bit
  uint64_t timestamp;
  struct block* next;
} block_t;

/**
 * A struct for storing the configuration of the cache as passed in
 * the cache_init function.
 */
typedef struct config {
  uint64_t C;
  uint64_t B;
  uint64_t S;
  enum REPLACEMENT_POLICY policy;
} config_t;

config_t* config = NULL;
uint64_t setSize = 0;
uint64_t numOfSets = 0;
block_t** head = NULL;
uint64_t* numOfBlksUsed = NULL;
block_t*** cache = NULL;

/**
 * Initializes your cache with the passed in arguments.
 *
 * @param C The total size of your cache is 2^C bytes
 * @param S The total number of blocks in a line/set of your cache are 2^S
 * @param B The size of your blocks is 2^B bytes
 * @param policy The replacement policy of your cache
 */
void cache_init(uint64_t C, uint64_t B, uint64_t S, enum REPLACEMENT_POLICY policy) {
    
  config = malloc(sizeof(config_t));
  config->C = C;
  config->B = B;
  config->S = S;
  config->policy = policy;

  setSize = (uint64_t) (1 << S);
  numOfSets = (uint64_t) (1 << (C - B - S));
  numOfBlksUsed = malloc(sizeof(uint64_t) * numOfSets);
  head = malloc(sizeof(block_t*) * numOfSets);

  cache = malloc(sizeof(block_t**) * numOfSets);
  for (uint64_t i = 0; i < numOfSets; i++) {
    cache[i] = malloc(sizeof(block_t*) * setSize);
    for (uint64_t j = 0; j < setSize; j++) {
      cache[i][j] = malloc(sizeof(block_t));
      cache[i][j]->tag = 0;
      cache[i][j]->valid = FALSE;
      cache[i][j]->dirty = FALSE;
      cache[i][j]->timestamp = 0;
    }
    for (uint64_t j = 0; j < setSize; j++) {
      uint64_t next = (j + 1) % setSize;
      cache[i][j]->next = cache[i][next]; 
    }
    numOfBlksUsed[i] = 0;
    head[i] = cache[i][0];
  } 
  return;
}

/**
 * Simulates one cache access at a time.
 *
 * @param rw The type of access, READ or WRITE
 * @param address The address that is being accessed
 * @param stats The struct that you are supposed to store the stats in
 * @return TRUE if the access is a hit, FALSE if not
 */
uint8_t cache_access(char rw, uint64_t address, cache_stats_t* stats) {
  uint64_t index = get_index(address, config->C, config->B, config->S);
  uint64_t tag = get_tag(address, config->C, config->B, config->S);
  stats->accesses++;
  block_t** set = cache[index];
  block_t* victim = NULL;

  for (uint64_t i = 0; i < setSize; i++) {
    block_t* block = set[i];
    if (block->valid == FALSE) {
      victim = block;
      break;
    }
    if (block->tag == tag) {
      if (config->policy == LRU) {
        for (uint64_t j = 0; j < setSize; j++) {
          if (set[j]->timestamp > block->timestamp) {
            set[j]->timestamp--;
          } 
        }
        block->timestamp = numOfBlksUsed[index] - 1;              
      }
      if (rw == READ) {
        stats->reads++;
      } else if (rw == WRITE) {
        block->dirty = TRUE;
        stats->writes++;
      }
      return TRUE;
    } 
  }
  if (rw == READ) {
    stats->reads++;     
    stats->read_misses++;
  } else if (rw == WRITE) {
    stats->writes++;
    stats->write_misses++;
  }
  if (victim != NULL) {
    victim->valid = TRUE;
    if (config->policy == LRU) {
      victim->timestamp = numOfBlksUsed[index];
      numOfBlksUsed[index]++;
    }
  } else {
    if (config->policy == FIFO) {
      victim = head[index];
      head[index] = head[index]->next;  
    } else if (config->policy == LRU) {
      for (uint64_t i = 0; i < setSize; i++) {
        if (set[i]->timestamp == 0) {
          victim = set[i];
          victim->timestamp = setSize - 1;
        } else {
          set[i]->timestamp--;
        }
      }
    }
    if (victim->dirty == TRUE) {
      stats->write_backs++;
    }
  }
  victim->tag = tag;
  victim->dirty = (rw == WRITE) ? TRUE : FALSE;
  return FALSE;
}

/**
 * Frees up memory and performs any final calculations before the
 * statistics are outputed by the driver
 */
void cache_cleanup(cache_stats_t* stats) {
  for (uint64_t i = 0; i < numOfSets; i++) {
    for (uint64_t j = 0; j < setSize; j++) {        
      free(cache[i][j]);
    }
    free(cache[i]);
  } 
  free(cache);
  free(config);
  free(numOfBlksUsed);
  free(head);
  stats->misses = stats->read_misses + stats->write_misses;
  stats->cache_access_time = 3;
  stats->memory_access_time = 120;
  stats->miss_rate = (double) stats->misses / stats->accesses;
  stats->avg_access_time = (double) (
    stats->cache_access_time + stats->miss_rate * stats->memory_access_time
  );
    
}

/**
 * Computes the tag of a given address based on the parameters passed
 * in
 *
 * @param address The address whose tag is to be computed
 * @param C The size of the cache (i.e. Size of cache is 2^C)
 * @param B The size of the cache block (i.e. Size of block is 2^B)
 * @param S The set associativity of the cache (i.e. Set-associativity is 2^S)
 * @return The computed tag
 */
uint64_t get_tag(uint64_t address, uint64_t C, uint64_t B, uint64_t S) {
  return address >> (C - S);
}

/**
 * Computes the index of a given address based on the parameters
 * passed in
 *
 * @param address The address whose tag is to be computed
 * @param C The size of the cache (i.e. Size of cache is 2^C)
 * @param B The size of the cache block (i.e. Size of block is 2^B)
 * @param S The set associativity of the cache (i.e. Set-associativity is 2^S)
 * @return The computed index
 */
uint64_t get_index(uint64_t address, uint64_t C, uint64_t B, uint64_t S) {
  uint64_t bitmask = (uint64_t) ((1 << (C - B - S)) - 1);
  bitmask = bitmask << B;
  return (address & bitmask) >> B;
}
