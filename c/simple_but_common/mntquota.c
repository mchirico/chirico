/* This finds all mounted devices with
   quotas implemented. Only devices with quotas
   are printed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mntent.h>
#include <string.h>

FILE *setdev()
{
	FILE *fp;
	if ((fp = setmntent(MOUNTED, "r")) == NULL) {
		fprintf(stderr, "Error calling setmntent\n");
	}
	return fp;
}



int getdev(FILE * fp,char *device)
{

	struct mntent *mnt;
        char *p;
        char *h;

	while ((mnt = getmntent(fp)) != NULL) {
		if (hasmntopt(mnt, "usrquota")) {
		  if ((h = hasmntopt(mnt,"loop=/dev/loop")) != NULL) {
                    snprintf(device,255,"%s",h+5);
		    p=device;
                    while(*p++) {
		      if ( *p == ',') {
			*p='\0';
			break;
		      }}
				return strlen(device);
			} else {
			  snprintf(device,255,"%s",mnt->mnt_fsname);
				return strlen(device);
			}
		}

	}



	return 0;
}

int main(void)
{

	FILE *fp;
	char device[256];


	if ((fp = setdev()) == NULL) {
		fprintf(stderr, "setdev returned NULL\n");
		exit(1);
	}



	while ( getdev(fp,device)) {
		printf("%s\n", device);

	}



	endmntent(fp);
	exit(0);

}
