#include <sys/types.h>
#include <unistd.h>
/* Needed for kill */
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
int
main (void)
{

  fprintf (stderr, "process id %d\n", getpid ());
  fprintf (stderr, "process parent pid %d\n", getppid ());
  while (1)
    {
      sleep (3);
      fprintf (stderr, "Program will kill itself in 1 second\n");
      sleep (1);
      kill (getpid (), SIGABRT);
    }
  return 0;
}
