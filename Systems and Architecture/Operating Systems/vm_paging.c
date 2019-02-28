#include "paging.h"
#include "page_splitting.h"
#include "swapops.h"
#include "stats.h"

fte_t *frame_table;

/*  --------------------------------- PROBLEM 2 --------------------------------------
  In this problem, you will initialize the frame table.

  The frame table will be located at physical address 0 in our simulated
  memory. You will first assign the frame_table global variable to point to
  this location in memory. You should zero out the frame table, in case for
  any reason physical memory is not clean.

  You should then mark the first entry in the frame table as protected. We do
   this because we do not want our free frame allocator to give out the frame
   used by the frame table.

  HINTS:
    - You will need to use the following global variables:
        - mem: Simulated physical memory already allocated for you.
        - PAGE_SIZE: The size of one page.
    - You will need to initialize (set) the following global variable:
        - frame_table: a pointer to the first entry of the frame table

  -----------------------------------------------------------------------------------
*/
void system_init(void) {
  frame_table = (fte_t*) mem;
  memset(frame_table, 0, PAGE_SIZE);
  frame_table[0].protected = TRUE;
}

/*  --------------------------------- PROBLEM 3 --------------------------------------
  This function gets called every time a new process is created.
  You will need to allocate a new page table for the process in memory using the
  free_frame function so that the	process can store its page mappings. Then, you
  will need to store the PFN of this page table in the process's PCB.

  HINTS:
        - Look at the pcb_t struct defined in pagesim.h to know what to set inside.
    - You are not guaranteed that the memory returned by the free frame allocator
    is empty - an existing frame could have been evicted for our new page table.
    - As in the previous problem, think about whether we need to mark any entries
    in the frame_table as protected after we allocate memory for our page table.
  -----------------------------------------------------------------------------------
*/
void proc_init(pcb_t *proc) {
  pfn_t pfn = free_frame();
  pte_t* pageTable = (pte_t*) (mem + pfn * PAGE_SIZE);
  memset(pageTable, 0, PAGE_SIZE);
  proc->saved_ptbr = pfn;
  frame_table[pfn].protected = TRUE;
}

/*  --------------------------------- PROBLEM 4 --------------------------------------
  Swaps the currently running process on the CPU to another process.

  Every process has its own page table, as you allocated in proc_init. You will
  need to tell the processor to use the new process's page table.

  HINTS:
    - Look at the global variables defined in pagesim.h. You may be interested in
        the definition of pcb_t as well.
  -----------------------------------------------------------------------------------
 */
void context_switch(pcb_t *proc) {
  PTBR = proc->saved_ptbr;
}

/*  --------------------------------- PROBLEM 5 --------------------------------------
  Takes an input virtual address and returns the data from the corresponding
  physical memory address. The steps to do this are:

  1) Translate the virtual address into a physical address using the page table.
  2) Go into the memory and read/write the data at the translated address.

  Parameters:
    1) address     - The virtual address to be translated.
    2) rw          - 'r' if the access is a read, 'w' if a write
    3) data        - One byte of data to write to our memory, if the access is a write.
             This byte will be NULL on read accesses.

  Return:
    The data at the address if the access is a read, or
    the data we just wrote if the access is a write.

  HINTS:
    - You will need to use the macros we defined in Problem 1 in this function.
    - You will need to access the global PTBR value. This will tell you where to
        find the page table. Be very careful when you think about what this register holds!
    - On a page fault, simply call the page_fault function defined in page_fault.c.
    You may assume that the pagefault handler allocated a page for your address
    in the page table after it returns.
    - Make sure to set the referenced bit in the frame table entry since we accessed the page.
    - Make sure to set the dirty bit in the page table entry if it's a write.
    - Make sure to update the stats variables correctly (see stats.h)
  -----------------------------------------------------------------------------------
 */
uint8_t mem_access(vaddr_t address, char rw, uint8_t data) {
  stats.accesses++;
  vpn_t vpn = vaddr_vpn(address);
  uint16_t offset = vaddr_offset(address);
  pte_t* pageTable = (pte_t*) (mem + PTBR * PAGE_SIZE);
  pte_t* entry = &pageTable[vpn];
  if (entry->valid == FALSE) {
    page_fault(address);
    stats.page_faults++;
  }
  pfn_t pfn = entry->pfn;
  frame_table[pfn].referenced = TRUE;
  paddr_t paddr = (pfn << OFFSET_LEN) | offset;
  if (rw == 'r') {
    stats.reads++;
    return mem[paddr];
  } else {
    mem[paddr] = data;
    entry->dirty = TRUE;
    stats.writes++;
    return data;
  } 
}

/*  --------------------------------- PROBLEM 9 --------------------------------------
  When a process exits, you need to free any pages previously occupied by the
  process. Otherwise, every time you closed and re-opened Microsoft Word, it
  would gradually eat more and more of your computer's usable memory.

  To free a process, you must clear the "mapped" bit on every page the process
  has mapped. If the process has swapped any pages to disk, you must call
  swap_free() using the page table entry pointer as a parameter.

  You must also clear the "protected" bits for the page table itself.
  -----------------------------------------------------------------------------------
*/
void proc_cleanup(pcb_t *proc) {
  pfn_t ptbr = proc->saved_ptbr;
  pte_t* pageTable = (pte_t*) (mem + ptbr * PAGE_SIZE);
  for (size_t i = 0; i < NUM_PAGES; i++) {
    pte_t* ptEntry = &pageTable[i];
    if (ptEntry->valid == TRUE) {
      pfn_t pfn = ptEntry->pfn;
      frame_table[pfn].mapped = FALSE;
      frame_table[pfn].referenced = FALSE;
    }
    if (ptEntry->swap != 0) {
      swap_free(ptEntry);
    }
  }
  frame_table[ptbr].protected = FALSE;
}
