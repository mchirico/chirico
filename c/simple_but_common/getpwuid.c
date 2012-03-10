#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>


int main(int argc, char **argv)
{

  struct passwd *pw;

  if(argc <= 1) {
      printf("./getpwuid  <username>\n");
      return 0;
  }
		 

  pw = getpwnam(argv[1]);
  if( pw != NULL ) {
    printf("User name %s\n",pw->pw_name);
    printf("user password %s\n",pw->pw_passwd);
    printf("user id %d\n",pw->pw_uid);
    printf("group id %d\n",pw->pw_gid);
    printf("real name %s\n",pw->pw_gecos);
    printf("home directory %s\n",pw->pw_dir);
    printf("shell program %s\n",pw->pw_shell);
 
  } else {
    printf("No such user\n");
  }
  return 0;

}

