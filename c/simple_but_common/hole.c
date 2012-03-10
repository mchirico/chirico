/*
  This example creates a hole in a file.

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

void err_sys(const char *s)
{
	fprintf(stderr, "Error %s\n", s);
}


int main(void)
{
	int fd;
	if ((fd =
	     open("file.hole", O_WRONLY | O_CREAT | O_TRUNC, 0660)) < 0)
		err_sys("creat error");

	if (write(fd, buf1, 10) != 10)
		err_sys("buf1 write error");
	/* offset now = 10 */

	if (lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");
	/* offset now = 16384 */

	if (write(fd, buf2, 10) != 10)
		err_sys("buf2 write error");
	/* offset now = 16394 */


	if (close(fd))
		err_sys("error in close");

	exit(0);
}
