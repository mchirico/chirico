/* Copyright (GPL) 2004, Mike Chirico mchirico@users.sourcefoge.net





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
#define MULT_START     16384
#define MULT_INCREMENT 2
#define INIT_SIZE      1024

size_t memindx = MULT_START;
size_t memnext;

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
size_t addmem(char **buf, size_t size)
{

  char *tbuf=NULL;
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
	size_t len = 0;
	char *buf = NULL;

	len = addmem(&buf, len);
	len = addmem(&buf, len);
	len = addmem(&buf, len);

	printf("length is %d\n", len);


	free(buf);
	return 0;

}
