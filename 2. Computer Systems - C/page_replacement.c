#include "types.h"
#include "pagesim.h"
#include "paging.h"
#include "swapops.h"
#include "stats.h"

pfn_t select_victim_frame(void);
pfn_t head = 0;
pfn_t tail = 1;
uint8_t isFull = FALSE;

/*  --------------------------------- PROBLEM 7 --------------------------------------
    Finds a free physical frame. If none are available, uses a clock sweep
    algorithm to find a used frame for eviction.

    Make sure you set the reference bits to 0 for each frame that had its
    referenced bit set.

    Return:
        The physical frame number of a free (or evictable) frame.

    HINTS: Use the global variables MEM_SIZE and PAGE_SIZE to calculate
    the number of entries in the frame table.
    ----------------------------------------------------------------------------------
*/
pfn_t select_victim_frame() { 
  if (isFull == FALSE) {
    pfn_t oldTail = tail;
    tail = (tail + 1) % NUM_FRAMES;
    if (tail == head) {
      isFull = TRUE;
    }
    return oldTail;
  }
  for (size_t i = 0; i < NUM_FRAMES; i++) {
    pfn_t oldHead = head;
    head = (head + 1) % NUM_FRAMES;
    tail = head;
    fte_t* entry = &frame_table[oldHead];
    if (entry->protected == FALSE) {
      if (entry->referenced == FALSE) {
        return oldHead;                
      } else {
        entry->referenced = FALSE;          
      }
    }   
  }
  for (size_t i = 0; i < NUM_FRAMES; i++) {
    pfn_t oldHead = head;
    head = (head + 1) % NUM_FRAMES;
    tail = head;
    fte_t* entry = &frame_table[oldHead];
    if (entry->protected == FALSE) {
      return oldHead;       
    }
  }
  printf("System ran out of memory\n");
  exit(1);
}

/*  --------------------------------- PROBLEM 8 --------------------------------------
    Make a free frame for the system to use.

    You will first call your page replacement algorithm to identify an
    "available" frame in the system.

    In some cases, the replacement algorithm will return a frame that
    is in use by another page mapping. In these cases, you must "evict"
    the frame by using the frame table to find the original mapping and
    setting it to invalid. If the frame is dirty, write its data to swap!
 * ----------------------------------------------------------------------------------
 */
pfn_t free_frame(void) {
  pfn_t victim_pfn;
  victim_pfn = select_victim_frame();
  fte_t* ftEntry = &frame_table[victim_pfn];     
  if (ftEntry->mapped == TRUE) {
    pfn_t ptbr = ftEntry->process->saved_ptbr;
    pte_t* pageTable = (pte_t*) (mem + ptbr * PAGE_SIZE);
    vpn_t vpn = ftEntry->vpn;
    pte_t* ptEntry = &pageTable[vpn];
    if (ptEntry->dirty == TRUE) {
      uint8_t* frame = mem + victim_pfn * PAGE_SIZE;
      swap_write(ptEntry, frame);
      stats.writebacks++;
      ptEntry->dirty = FALSE;
    }
    ptEntry->valid = FALSE;    
  }
  ftEntry->mapped = FALSE;
  return victim_pfn;
}
