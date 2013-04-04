#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>

#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define COPYINCR (1024*1024*1024)	/* 1 GB */


int main(int argc, char *argv[])
{


    int fdin, fdout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;


    if (argc != 3) {
        fprintf(stderr,"usage: %s <fromfile> <tofile>\n", argv[0]);
        return 0;
    }


    if ((fdin = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr,"can't open %s for reading\n", argv[1]);
        return 0;
    }


    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
      {
        fprintf(stderr,"can't creat %s for writing\n", argv[2]);
	return 0;
      }


    if (fstat(fdin, &sbuf) < 0)	/* need size of input file */
      {
        fprintf(stderr,"fstat error\n");
	return 0;
      }


    if (ftruncate(fdout, sbuf.st_size) < 0)	/* set output file size */
      {
        fprintf(stderr,"ftruncate error\n");
	return 0;
      }
    

    while (fsz < sbuf.st_size) {

        if ((sbuf.st_size - fsz) > COPYINCR)
            copysz = COPYINCR;
        else
            copysz = sbuf.st_size - fsz;


        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED,fdin, fsz)) == MAP_FAILED)
	  {
            fprintf(stderr,"mmap error for input\n");
	    return 0;
	  }

        if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
	  {
            fprintf(stderr,"mmap error for output\n");
	    return 0;
	  }
	

        memcpy(dst, src, copysz);	/* does the file copy */
        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;

    }

    exit(0);

}
