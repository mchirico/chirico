/* hwwrite.c - Demonstration of creating and writing to a file */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fd;

    /* open the file, creating it if it's not there, and removing
       its contents if it is there */
    if ((fd = open("hw", O_TRUNC | O_CREAT | O_WRONLY, 0644)) < 0) {
        perror("open"), 
        exit(1);
    }

    /* the magic number of 13 is the number of characters which will
       be written */
    if (write(fd, "Hello World!\n", 13) != 13) {
        perror("write");
        exit(1);
    }

    close(fd);

    return 0;
}
