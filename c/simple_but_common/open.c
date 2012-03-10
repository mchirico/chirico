#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>

#define BUFLEN 100
extern int errno;


int
main (void)
{
  int fp,error;
  char buf[BUFLEN+1];

  if ((fp = open ("data", O_RDWR | O_CREAT | O_APPEND, 0600)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      return 1;
    }

  snprintf (buf, BUFLEN, "123\n");
  write (fp, buf, strlen (buf));

  /* Restart close should a signal occur */
  while((( error = close (fp) ) == -1) && (errno == EINTR));
  if(error == -1)
    perror("Failed to close the file\n");

  return 0;

}
