/*

  Very simple read example that you can pipe data too

   $cat read.c |./read

*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pty.h>

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>
extern int errno;

#define BUFS 1024
int
main (void)
{
  int fd,n;
  char buf[BUFS+1];


  if ((fd = open ("data2", O_RDWR | O_CREAT, 0600)) == -1)
    {
      fprintf(stderr, "Can't open data: %s\n", strerror (errno));
      return 1;
    }


  write(fileno(stdout),"this is from pipedrv2",strlen("this is from pipedrv2"));
  n=read(fileno(stdin), buf, BUFS );
  buf[n]='\0';
  write (fd, buf, strlen (buf));

  close (fd);

  if( n < 0 )
    fprintf(stderr,"Problem in read\n");

  if( n == 0 )
    fprintf(stderr,"Terminated normally\n");

  return 0;

}
