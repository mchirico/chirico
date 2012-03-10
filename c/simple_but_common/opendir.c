/*  Copyright (c) GPL 2004  Mike Chirico mchirico@users.sourceforge.net or mchirico@comcast.net

    Warning ctime uses static storage and returns a newline. So do not
    call it twice within one print statement or you could clobber results.

    Putting data in buf is necessary because nodeinfo needs the full
    path and file name. dentp->d_name is only the file name.

*/
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#define BUFLEN    5000


int notdot(const char *node)
{
  int flag=0;
  while(*node && flag==0)
    {
      if(*node != '.') {
	if(*node != '\\') { flag = 1; }
        }
       node++;
    }
  return flag;
}

void nodeinfo(const char *node)
{
	struct stat statb;
        struct dirent *dentp;
	DIR *dp;
        char buf[BUFLEN+2];
	char tbuf[30];

	if (lstat(node, &statb) == -1) {
		fprintf(stderr, "Error getting status for %s \n", node);
		if (errno == EBADF)
			fprintf(stderr, "filedes is bad");
		if (errno == ENOENT)
			fprintf(stderr, "component does not exist");
		if (errno == ENOTDIR)
			fprintf(stderr, "component of path not dir");
		if (errno == EACCES)
			fprintf(stderr, " Permission denied");
		if (errno == ENOMEM)
			fprintf(stderr, " Out of memory");
		if (errno == ENAMETOOLONG)
			fprintf(stderr, " File name too long");
	} else {




		strftime(tbuf,30,"%Y-%m-%d %T",localtime(&statb.st_atime));
                printf("%s a %s", node,tbuf);

		strftime(tbuf,30,"%Y-%m-%d %T",localtime(&statb.st_mtime));
		printf(",m %s", tbuf);

		strftime(tbuf,30,"%Y-%m-%d %T",localtime(&statb.st_ctime));
		printf(",s %s",tbuf);


		printf(",s# %ld", statb.st_ino);
		printf(",size(bytes) %ld", statb.st_size);

                printf(",mode %o",statb.st_mode);
                printf(",nlink %d",statb.st_nlink);
                printf(",devid %d",(int)statb.st_dev);
                printf(",uid %d",statb.st_uid);
                printf(",gid %d\n",statb.st_gid);

                if (S_ISDIR(statb.st_mode) )
		  {
		    printf("  directory %s\n",node);
                    if ((dp = opendir(node)) == NULL) {
		      fprintf(stderr," (node:Cannot open directory %s) ",node);
		    }else {
                      while((dentp = readdir(dp)) != NULL) {
			if(notdot(dentp->d_name)) {  
                          snprintf(buf,BUFLEN,"%s/%s",node,dentp->d_name);
			  nodeinfo(buf);
			}
		      }
              		while ((closedir(dp) == -1) && (errno == EINTR));
                   }
 
                  }
	}
}





int main(int argc, char **argv)
{
	struct dirent *dentp;
	DIR *dp;
	char buf[BUFLEN+2];

	if (argc < 2) {
		fprintf(stderr, "Usage: %s dir1 dir2 ... dirN\n", argv[0]);
		return 1;
	}


	while (--argc >= 1) {
		if ((dp = opendir(argv[argc])) == NULL) {
			fprintf(stderr, "Cannot open directory %s\n",
				argv[argc]);
			return 2;
		}
		while ((dentp = readdir(dp)) != NULL) {
			snprintf(buf, BUFLEN, "%s/%s", argv[argc],
				 dentp->d_name);
			if(notdot(dentp->d_name)) 
			  nodeinfo(buf);
		}

		while ((closedir(dp) == -1) && (errno == EINTR));
	}
	return 0;


}
