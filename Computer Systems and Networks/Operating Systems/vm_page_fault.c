#include "paging.h"
#include "swapops.h"
#include "stats.h"

/*  --------------------------------- PROBLEM 6 --------------------------------------
    Page fault handler.

    When the CPU encounters an invalid address mapping in a page table,
    it invokes the OS via this handler.

    Your job is to put a mapping in place so that the translation can
    succeed. You can use free_frame() to make an available frame.
    Update the page table with the new frame, and don't forget
    to fill in the frame table.

    Lastly, you must fill your newly-mapped page with data. If the page
    has never mapped before, just zero the memory out. Otherwise, the
    data will have been swapped to the disk when the page was
    evicted. Call swap_read() to pull the data back in.

    HINTS:
         - You will need to use the global variable current_process when
           setting the frame table entry.

    ----------------------------------------------------------------------------------
 */
void page_fault(vaddr_t address) {
  vpn_t vpn = vaddr_vpn(address);
  pte_t* pageTable = (pte_t*) (mem + PTBR * PAGE_SIZE);
  pte_t* ptEntry = &pageTable[vpn];
  pfn_t pfn = free_frame();
  ptEntry->valid = TRUE;
  ptEntry->pfn = pfn;
  fte_t* ftEntry = &frame_table[pfn];
  ftEntry->mapped = TRUE;
  ftEntry->process = current_process;
  ftEntry->vpn = vpn;
  uint8_t* frame = mem + pfn * PAGE_SIZE;
  if (ptEntry->swap != 0) {
    swap_read(ptEntry, frame);
  } else {
    memset(frame, 0, PAGE_SIZE);
  }
}
