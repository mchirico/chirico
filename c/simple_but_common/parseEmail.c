#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chrchk(char c)
{
  char *s=" \n\r,\\\t|{}[]/?;:";
  while(*s){
    if (*s == c)
      return 1;
    s++;
  }
  return 0;
}

void free_array(char ***t)
{
  char **p=*t;
  char **op=p;

  if(p == NULL)
    return;

     while(*p != NULL) {
       free(*p);
       ++p;
     }
       free(op);
}



char **build_array(char *s)
{
	char **argv;
	char *p;
	char *t;
	char *k;
	size_t i=0, j=0, index=0;

        /* We won't have more than strlen(s)items in our array */
	if (strlen(s) <= 0 )
	  return NULL;
	argv = malloc(strlen(s)*sizeof(char *));
	p = s;
	t = p;
	while (*p != '\0') {
		if (chrchk(*p)) {
		  if(i > j) {
		    k = (char *) malloc(sizeof(char *)* (i-j)+1);
		    strncpy(k,t,(int)(i-j));
		    k[(i-j)]='\0';
		    argv[index++]=k;
		    argv[index]=NULL;
		    j=i;
		      }
			while (chrchk(*p)) {
			  ++i;
			  ++j;
			  ++p;
			}
			t=p;
		}

		if (*p != '\0') {
			++i;
			p++;
		}
	}
	/* This is the last string, if not terminated by \0*/
	  if(i > j) {
		    k = (char *) malloc(sizeof(char *)* (i-j)+1);
		    strncpy(k,t,(int)(i-j));
		    k[(i-j)]='\0';
		    argv[index++]=k;
		    argv[index]=NULL;
	  }

	return argv;
}


int main(void)
{
  char **p = build_array("mchirico@gmail.com,bob.bozo@dork.com,stuff@here.com  more@here.com"
			 "[zod@cnet.com|garp@dump.com{pick@par.com||\\last@last.com  "
);
  char **beg=p;

  if (p == NULL)
    return 0;

     while(*p != NULL) {
       fprintf(stderr,"%s\n",*p);
       ++p;

     }
     free_array(&beg);
}
