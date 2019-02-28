#include "paging.h"
#include "stats.h"

stats_t stats;

/*  --------------------------------- PROBLEM 10 -------------------------------------
    Calculate any remaining statistics to print out.

    You will need to include code to increment many of these stats in
    the functions you have written for other parts of the project.

    Use this function to calculate any remaining stats, such as the
    average access time (AAT).

    You may find the #defines in the stats.h file useful.
  -----------------------------------------------------------------------------------
*/
void compute_stats() {
  double pageFaultRate = (double) stats.page_faults / stats.accesses;
  double writeBackRate = (double) stats.writebacks / stats.accesses;
  stats.aat = (
    MEMORY_READ_TIME
      + DISK_PAGE_READ_TIME * pageFaultRate
      + DISK_PAGE_WRITE_TIME * writeBackRate
  );
}
