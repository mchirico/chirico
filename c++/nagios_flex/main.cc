/*   Copyright (C) 2006  Mike Chirico <mchirico@users.sourceforge.net>
 
     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.
 
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
 
     You should have received a copy of the GNU General Public License along
     with this program; if not, write to the Free Software Foundation, Inc.,
     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.  */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>		/* for strerror(int errno) */
#include <errno.h>


extern int num_lines;
extern int num_chars;
extern int state_chg[];
extern int i;
extern int fp0,fp1,fp2,fp3,fp4,fp5;
extern void yylex();

int open_load_file() {
  int fp;
  if ((fp = open ("data_load", O_RDWR | O_CREAT | O_APPEND, 0600)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      exit(1);
    }
  return fp;
}

int open_mem_file() {
  int fp;
  if ((fp = open ("data_mem", O_RDWR | O_CREAT | O_APPEND, 0600)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      exit(1);
    }
  return fp;
}

int open_process_file() {
  int fp;
  if ((fp = open ("data_process", O_RDWR | O_CREAT | O_APPEND, 0600)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      exit(1);
    }
  return fp;
}
int open_disk_file() {
  int fp;
  if ((fp = open ("data_disk_partition", O_RDWR | O_CREAT | O_APPEND, 0600)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      exit(1);
    }
  return fp;
}



int main(int argc, char **argv)
{

	int i;
	extern FILE *yyin, *yyout;

	if(argc==1) {
	  fprintf(stderr,"Usage:\n\tnparse <filename>\n\n");
          return 0;
	}

        fp0=open_load_file();
        fp1=open_mem_file();
        fp2=open_process_file();
        fp3=open_disk_file();

	while (--argc) {
		yyin = fopen((const char *) argv[argc], "r");
		if (yyin == NULL) {	/* open failed */
			exit(1);
		}
		for (i = 0; i < 3; ++i) {
			state_chg[0] = 1;
		}
		yylex();
	}

        close(fp0);
        close(fp1);
        close(fp2);
        close(fp3);
        close(fp4);
        close(fp5);
	return 0;
}
