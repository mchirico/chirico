#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
  DIR *dp;
  struct dirent *dirp;

  if (argc != 2)
    {
      fprintf(stderr,"usage: ls directory_name\n");
      exit(EXIT_FAILURE);
    }

  if ((dp = opendir(argv[1])) == NULL)
    {
      fprintf(stderr,"Cannot open %s\n",argv[1]);
      exit(EXIT_FAILURE);
    }    

  while ((dirp = readdir(dp)) != NULL)
    printf("%s type=%d\n", dirp->d_name,dirp->d_type);

  closedir(dp);

  exit(EXIT_SUCCESS);
}
