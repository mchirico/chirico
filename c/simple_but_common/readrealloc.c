/* Copyright (GPL) 2004, Mike Chirico mchirico@users.sourcefoge.net


 This program copies data "binary or text" from "data" to "dataout"
 reading all the input into memory first.


 Always check your work:
   Works for valgrind 2.2.0 (http://valgrind.kde.org/)

   $ valgrind --logfile=valgrind.output   --tool=memcheck ./a.out



*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>		/* for strerror(int errno) */
#include <errno.h>

extern int errno;

#define MULT_START     16384
#define MULT_INCREMENT 2
#define INIT_SIZE      1024

long memindx = MULT_START;
long memnext;

/*
#define MULT_START     16384
#define MULT_INCREMENT 2
#define INIT_SIZE      1024

   Size increment:


          17408   
	  50176  
 	  115712 
	  246784 
	  508928 
	  1033216
	  2081792

*/
long addmem(char **buf, long size)
{
  char *tbuf;

	memnext = (size > 0) ? size + memindx : INIT_SIZE;
	memindx = memindx * MULT_INCREMENT;


	tbuf = realloc(*buf, memnext);
	if (tbuf == NULL) {
		fprintf(stderr, "Can't allocate memory in addmem\n");
		return size;
	} else {
		*buf = tbuf;
		return memnext;
	}




}

int main()
{
	int fd, fd2, n;
	long len = 0, totread = 0;
	char *buf = NULL, *pbuf = NULL;

        int numread=0;

	if ((fd = open("data", O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "Can't open data: %s\n", strerror(errno));
		return 1;
	}

	if ((fd2 = open("dataout", O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "Can't open data: %s\n", strerror(errno));
		return 1;
	}



	while (len - totread - 1 < 1024)
		len = addmem(&buf, len);

	pbuf = buf;

	fprintf(stderr, "len - totread -1 %ld\n", len - totread - 1);

	while ((n = read(fd, pbuf, 1024)) > 0) {
		totread += n;
		pbuf[n] = '\0';  // This is for printing test
		while (len - totread - 1 < 1024)
			len = addmem(&buf, len);

		pbuf = &buf[totread];

                numread+=1; // just for stats
	}
	write(fd2, buf, totread);

	close(fd2);
	close(fd);


        printf("\n\nThis program copies the data in \"data\" to \"dataout\"\n");
        printf(";but, putting the contents into mem var buf, reallocating as needed.\n\n");
        printf("Stats:\n");
	printf("  Length allocated for buf %ld\n", len);
	printf("  Number of reads %d\n\n", numread);


	free(buf);
	return 0;

}
