#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLINE 256

int main(void)
{

  int fd;

  char line[MAXLINE + 1];
  ssize_t n;


  if ((fd = open ("deleteme_junk.txt", O_RDWR | O_CREAT, 0600)) == -1)
    {
      fprintf(stderr, "Can't open deleteme_junk.txt:\n");
      return 1;
    }


  snprintf(line,MAXLINE,"Sample text");
  write(fd,line,MAXLINE);
  close(fd);



  if ((fd = open ("deleteme_junk.txt", O_RDWR | O_CREAT, 0600)) == -1)
    {
      fprintf(stderr, "Can't open deleteme_junk.txt:\n");
      return 1;
    }



  while ( ( n=read(fd, line, MAXLINE )) >  0)
    {

       line[n] = '\0';
       printf("%s", line);
    }

  close(fd);
  return 0;

}
    
