/*
Download:
http://prdownloads.sourceforge.net/cpearls/simple_but_common.tar.gz?download

  Sample usage:

    $ .getline
       Enter some text here
       and more text
       ^D

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

int main(void)
{

  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, stdin)) != -1) {
    printf("Retrieved line of length %u :\n", read);
    printf("%s", line);
  }
  if (line)
    free(line);
  return EXIT_SUCCESS;
}
