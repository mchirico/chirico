#include <stdio.h>
#include <sys/mman.h>		// Needed for mlockall()
#include <unistd.h>		// needed for sysconf(int name);
#include <malloc.h>
#include <sys/time.h>		// needed for getrusage
#include <sys/resource.h>	// needed for getrusage


#define SOMESIZE (100*1024)	// 100kB


int
main (int argc, char *argv[])
{
  // Allocate some memory
  int i, page_size;
  char *buffer;
  struct rusage usage;


  // Now lock all current and future pages from preventing of being paged
  if (mlockall (MCL_CURRENT | MCL_FUTURE))
    {
      perror ("mlockall failed:");
    }


  page_size = sysconf (_SC_PAGESIZE);
  buffer = malloc (SOMESIZE);


  // Touch each page in this piece of memory to get it mapped into RAM
  for (i = 0; i < SOMESIZE; i += page_size)
    {
      // Each write to this buffer will generate a pagefault.
      // Once the pagefault is handled a page will be locked in memory and never
      // given back to the system.
      buffer[i] = 0;
      // print the number of major and minor pagefaults this application has triggered
      getrusage (RUSAGE_SELF, &usage);
      printf ("Major-pagefaults:%d, Minor Pagefaults:%d\n", usage.ru_majflt,
	      usage.ru_minflt);
    }
  // buffer is never released, or swapped, so using it from now will never lead to any pagefault


  //<do your RT-thing>


  return 0;
}
