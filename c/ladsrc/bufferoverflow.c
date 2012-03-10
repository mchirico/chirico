/* bufferoverflow.c - A simple example of a buffer overflow */

#include <limits.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
    char path[_POSIX_PATH_MAX];

    printf("copying string of length %d\n", strlen(argv[1]));

    strcpy(path, argv[1]);

    return 0;
}

