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



size_t addmem(char **buf, size_t size)
{

	char *tbuf;

	size_t memnext = 0;

	if (size < 10) {
		memnext = 1024;
	} else {

		if (size > 67108864) {
			memnext = (size_t) size + 65536;
		} else {
		  memnext = (size_t) size * 2;
		}


	}

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
	int i = 0;

	for (i = 0; i < 200; ++i) {

		len = addmem(&buf, len);
		printf("length is %d\n", len);
	}


	free(buf);
	return 0;

}
