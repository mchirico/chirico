/*
   Example of using popen. 

*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>

FILE *Popen(const char *command, const char *mode)
{
	FILE *fp;

	if ((fp = popen(command, mode)) == NULL)
		fprintf(stderr, "popen error");
	return (fp);
}

int Pclose(FILE * fp)
{
	int n;

	if ((n = pclose(fp)) == -1)
		fprintf(stderr, "pclose error");
	return (n);
}

char *Fgets(char *ptr, int n, FILE * stream)
{
	char *rptr;

	if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		fprintf(stderr, "fgets error");

	return (rptr);
}

void Fputs(const char *ptr, FILE * stream)
{
	if (fputs(ptr, stream) == EOF)
		fprintf(stderr, "fputs error");
}



extern int errno;

#define MAXLINE 1024
int main(void)
{
	FILE *fp;
	char buf[MAXLINE + 1];

	fp = Popen("ls -l", "r");

	while (Fgets(buf, MAXLINE, fp) != NULL)
		Fputs(buf, stdout);

	Pclose(fp);
	return (1);
}
