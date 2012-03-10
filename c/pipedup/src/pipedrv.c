/*  Copyright (c)  GPL 2006
    mmc Mike Chirico mchirico@users.sourceforge.net



*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>
#include "wrapper.h"
extern int errno;


#define BUFS 2048


static void *asyc_read(void *arg)
{
  int fd,n,i=0;
  char s[BUFS+1];
  pthread_t t;

  fprintf(stderr,"in asyc_read before detach\n");

  fd = *((int *) arg);
  Pthread_detach(pthread_self());
  fprintf(stderr,"in asyc_read after detach\n");
  while ((n = read(fileno(stdin), s, BUFS)) > 0){
     s[n] = '\0';
     ++i;
     fprintf(stderr,"ASYC_READ (while i=%d) writing the following ->%s\n<-",i,s);
      write(fd, s, strlen(s));
      Pthread_create(&t, NULL, &asyc_read, &fd);
  }

  s[n] = '\0';
  fprintf(stderr,"2 ASYC_READ (i=%d)*************************************************** writing the following ->%s<-\n",i,s);
  write(fd, s, strlen(s));
  //  Pthread_create(&t, NULL, &asyc_read, &fd);

  //free(s); -- no not here, didn't allocate
  //free(arg); -- no not here, didn't allocate

  return (NULL);
}

int sndcmd(int fd, char *s)
{

  int n;
  char buf[BUFS + 1];

        pthread_t t;

	fprintf(stderr,"sndcmd= %s Before asyc_read.\n",s);
        Pthread_create(&t, NULL, &asyc_read, &fd);



  write(fileno(stdout), s, strlen(s));


	fprintf(stderr,"sndcmd= %s After asyc_read.\n",s);

        //I don't think we need this 
	/*  n = read(fileno(stdin), buf, BUFS);
	    buf[n] = '\0'; */

	fprintf(stderr,"just finished last read.\n",s);
	sleep(1);
  return n;

  /*

	int n;
        pthread_t t;

        Pthread_create(&t, NULL, &asyc_read, &fd);
	n=write(fileno(stdout), s, strlen(s));
        fprintf(stderr,"sending the following %s\n",s);


        fprintf(stderr,"in sndcmd\n");
	return n;
  */
}



void *f1(void *arg)
{
	int i;
	int max = (int) arg;

	for (i = 0; i < max; ++i)
		fputc('x', stderr);
	return NULL;
}

void *f2(void *arg)
{
	int i;
	int max = (int) arg;

	for (i = 0; i < max; ++i)
		fputc('y', stderr);
	return NULL;
}

/* The main program.  */

int main()
{
	int fd, fd2, n;
	pthread_t thread_id[2];
	int i;
	int count = 120;



	if ((fd = open("pipe_data", O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "Can't open data: %s\n", strerror(errno));
		return 1;
	}

	if ((fd2 = open("cmds", O_RDWR )) == -1) {
		fprintf(stderr, "Can't open cmds: %s\n", strerror(errno));
		fprintf(stderr, "Create the file cmds with ssh commands but make\n");
		fprintf(stderr, "sure you add exit as the last line.\n");
		return 1;
	}







        n=sndcmd(fd,"netstat -na\n");
        n=sndcmd(fd,"ls -l\n");
        n=sndcmd(fd,"w\n");
        n=sndcmd(fd,"sar\n");
        n=sndcmd(fd,"date\n");
        n=sndcmd(fd,"cat /proc/cpuinfo\n");
        n=sndcmd(fd,"df -lh\n");
        n=sndcmd(fd,"cat /proc/slabinfo\n");
        n=sndcmd(fd,"exit\n");




	Pthread_create(&thread_id[0], NULL, &f1, (void *) count);
	Pthread_create(&thread_id[1], NULL, &f2, (void *) count);
	/* Print o's continuously to stderr.  */
	for (i = 0; i < count; ++i) {
		fputc('o', stderr);
	}
	Pthread_join(thread_id[1], NULL);
	Pthread_join(thread_id[0], NULL);


        close(fd2);





	close(fd);
	if (n < 0)
		fprintf(stderr, "Problem in read\n");

	if (n == 0)
		fprintf(stderr, "Output in pipe_data\nTerminated normally.\n");


	return 0;











	return 0;
}
