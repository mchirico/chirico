#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>

#define BUFLEN 1024
#define BUFFCT  1024
extern int errno;


int
main (void)
{
  int fp,error,flag=0;
  unsigned int n,i,j;
  char buf[BUFLEN+1],bufb[BUFFCT*BUFLEN+1];

  if ((fp = open ("data", O_RDWR, 0600)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      return 1;
    }

  bufb[0]='\0';
  j=0;
  while(( n=read(fp,buf,BUFLEN))> 0)
    {
      buf[n]='\0';
      for(i=0; i < strlen(buf); ++i)
	{
	  if(buf[i]!='\n' && buf[i]!='\r' && buf[i]!=' ' && buf[i]!='\0') 
          {
	    bufb[j++]=buf[i];
            flag=0;
	  } else 
	    {
              if(buf[i]=='\n')
                {
          	  flag=j;
		bufb[j++]=',';
                }
	    }
                  
          
        }
     
    }
  bufb[j]='\0';
  if(flag)
    bufb[flag]='\0';


  fprintf(stderr,"%s\n",bufb);
  //write (fp, buf, strlen (buf));

  // Restart close should a signal occur */
  while((( error = close (fp) ) == -1) && (errno == EINTR));
  if(error == -1)
    perror("Failed to close the file\n");

  return 0;

}
