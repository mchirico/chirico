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

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>
extern int errno;

#define BUF_LEN 8192

/* Debug stuff */

int numcalls = 0;



size_t addmem(char **buf, size_t size)
{

	char *tbuf;
	size_t memnext = 0;
	if (size < (BUF_LEN + 1)) {
		memnext = BUF_LEN * 2;
	} else {
		if (size > 67108864) {
			memnext = (size_t) size + 65536;
		} else {
			memnext = (size_t) size *2;
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



char *Read(int fd)
{
	char buf[BUF_LEN + 1];
	ssize_t n = 0;
	size_t mem = 0;
	size_t total_mem = 0;
	char *p = NULL;

	while ((n = read(fd, buf, BUF_LEN)) > 0) {
		buf[n] = '\0';
		total_mem += (size_t)n;
		if (mem <= total_mem) {
			/* May need to initilize p or just add mem */
			if (mem <= 0) {
				mem = addmem(&p, mem);
				p[0] = '\0';
			} else {
				mem = addmem(&p, mem);
			}
		}

		
		strncat(p, buf, (size_t)n);
	}
	return p;
}

ssize_t Write(int fd, char *p, size_t nb)
{
	char *s = NULL;
	size_t slen = 0;

	ssize_t n = 0, tlen = 0;

	s = p;
	slen = strlen(p);
	tlen = (ssize_t) slen;


	if (slen > nb)
		slen = nb;


	while ((n = write(fd, s, slen)) > 0) {
		tlen = tlen - n;
		s = s + n;
		slen = strlen(s);


	if (slen > nb)
		slen = nb;



		numcalls += 1;
	}

	return (ssize_t) tlen;

}




int main(void)
{
        int fd;
	char *p;


	if ((fd = open("data", O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "Can't open data: %s\n", strerror(errno));
		return 1;
	}


	fprintf(stderr,
		"Enter some text. Writes to file \"data\".  Ctl-D to end\n");

	p = Read(fileno(stdin));
	//	Write(fd, p, 16384);
	Write(fd, p, strlen(p));
	free(p);
	close(fd);

	fprintf(stderr, "Number of calls %d\n", numcalls);

	return 0;

}
