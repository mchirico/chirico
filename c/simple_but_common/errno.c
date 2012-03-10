#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>
extern int errno;

#define MAXLINE 256
int
main (void)
{
  int fp;
  int i;
  int error;
  char buf[MAXLINE];
  char *strErr = NULL;

  for (i = 0; i < 126; ++i)
    printf ("errno: %d message: %s\n", i, strerror (i));

  if ((fp = open ("List_of_error_messages", O_RDWR | O_CREAT, 0600)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      return 1;
    }


  /*   char * strerror_r(int errnum, char *buf, size_t n)  -- thread safe version */
  /*   This may or may not use buf!  */
  /*   gcc uses char * and not int  */

  for (i = 0; i < 126; ++i)
    if ((strErr = strerror_r (i, buf, MAXLINE)) != NULL)
      {
	snprintf (buf, MAXLINE, "errno: %d string: %s\n", i, strErr);
	write (fp, buf, strlen (buf));
      }
    else
      {
	fprintf (stderr, "Call to strerror_r failed \n");
	return 1;
      }

  /* restarts close if a signal occurs */
  while((( error = close (fp) ) == -1) && (errno == EINTR));
  if(error == -1)
    perror("Failed to close the file\n");

  return 0;

}
