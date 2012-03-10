/* Mike Chirico mchirico@users.sourceforge.net

   Example of using the system command where output is redirected
   to a file using the dup2 command, then, lseek starts the read
   at the beginning of the file.
 
   This way nothing show up on the screen until data has been
   filtered through the read.


*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>             /* for strerror(int errno) */
#include <errno.h>
extern int errno;

const size_t BUFS= 1024;

int
main (void)
{
  int fd,n;
  char buf[BUFS+1];


  if ((fd = open ("data", O_RDWR | O_CREAT, 0600)) == -1)
    {
      fprintf(stderr, "Can't open data: %s\n", strerror (errno));
      return 1;
    }
  
  if( dup2(fd,STDOUT_FILENO) == -1 )
    {
      fprintf(stderr,"Can't dup2: %s\n", strerror(errno));
    }
  
  if( system("ls -l") == -1 )
    {
      fprintf(stderr,"Can't system: %s\n",strerror(errno));
      close(fd);
      return 1;
    }


  if( lseek (fd, (off_t) 0, SEEK_SET) == -1)
    {
     fprintf(stderr,"Can't lseek: %s\n",strerror(errno));
     return 1;
    }



  while ( ( n=read(fd, buf, BUFS )) >  0)
    {
      buf[n]='\0';
      fprintf(stderr,"out: %s\n",buf);
    }
  close (fd);

  if( n < 0 )
    fprintf(stderr,"Problem in read\n");

  if( n == 0 )
    fprintf(stderr,"Terminated normally\n");

  return 0;

}



