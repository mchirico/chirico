/*


  Very simple read example to read a random number
  from /dev/urandom

   $ ./rand

*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>
extern int errno;

#define BUFS 4


/* This assumes ssize_t is 4 bytes on your system */

union U {
  ssize_t mlong;
  char c[4];
};

int main (void)
{
  int fp,n;
  char buf[BUFS+1];
  union U u;
  
  /*  /dev/random only returns bytes when enough noise has 
      been generated from the entropy pool. Hense you may 
      be blocked waiting. In contrast, /dev/urandom will always 
      return bytes. */
  if ((fp = open ("/dev/urandom", O_RDONLY)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      return 1;
    }



 if ( ( n=read(fp, buf, BUFS )) >=  4)
   {
     buf[n]='\0';
     u.c[0]=buf[0];
     u.c[1]=buf[1];
     u.c[2]=buf[2];
     u.c[3]=buf[3];

     /* Uncomment  to check sizes
	fprintf(stderr,"%u %d  sizeof(%d)  sizeof(%d)\n",u.mlong,n,sizeof(u.mlong),sizeof(u)); */
     printf("%u\n",u.mlong);

   }
 close(fp);

  return 0;

}
