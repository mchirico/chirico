#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*

gcc -g -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings buildarray.c  -o buildarray   -lfl
valgrind --leak-check=yes ./buildarray
*/


/*
  Build Array
*/
char **barr(char ***argv, const char *s)
{
	char **tbuf = NULL;
	char **targv = NULL;
	size_t i = 0;

	targv = *argv;

	if (strlen(s) != 0) {
		/* see how big argv is */
		while (targv != NULL && *targv != NULL) {
			++i;
			++targv;
		}
		tbuf = realloc(*argv, sizeof(char *) * (i + 2));
		if (tbuf != NULL) {
			targv = tbuf;
			char *p = malloc(sizeof(char) * (strlen(s) + 1));
			strncpy(p, s, strlen(s) + 1);
			targv[i] = p;
			targv[i + 1] = NULL;
		}
	}
	return targv;

}

/* Find string in Array
*/
char *findarr(char **argv, const char *s, int *i)
{
  char *t=NULL;
  *i=0;

	while (argv != NULL && *argv != NULL) {
	  t = strstr(argv[0],s);
	  if (t != NULL){
	    return argv[0];
	  }
		++argv;
		*i=*i+1;
	}
	return NULL;

}







/* Print string array */
void prarr(char **argv)
{
	while (argv != NULL && *argv != NULL) {
		fprintf(stderr, "%s\n", *argv);
		++argv;
	}

}
/*   Free memory allocated to the array
*/
void freearr(char ***argv)
{
	char **targv = NULL;
	char **head = NULL;

	targv = *argv;
	if (targv == NULL)
		return;

	head = targv;
	while (targv != NULL && *targv != NULL) {
		free(targv[0]);
		++targv;
	}
	free(head);

}


/*
  Replace string in array
*/
int rarr(char ***argv,const char *s,const char *r)
{
  char **targv=*argv;
  char *t=NULL;
  char *tp=NULL;
  int i=0;
  size_t lent=0;
  size_t len0=0;
  size_t len1=0;
  size_t lenr=0;
  size_t lens=0;
  size_t len_=0;

  char *sp=NULL;
  char *ep=NULL;



	while (targv != NULL && *targv != NULL) {
	  t = strstr(targv[0],s);
	  if (t != NULL){
	    

	    sp=(*argv)[i];
	    lent=strlen(sp);
	    ep=t;
	    *t='\0';
	    len0=strlen(sp);
	    len1=strlen(ep+1);
	    lenr=strlen(r);
	    lens=strlen(s);
	    len_=len0+len1+lenr+2;
	    tp = (char *) malloc (sizeof(char)*(len_+1));
	    snprintf(tp,len_,"%s%s%s",sp,r,ep+lens);

	    (*argv)[i]=tp;
	    free(sp);


	  }
	  ++i;
	  ++targv;
	}

	return 1;


}




int main(void)
{
  char *s;
  int i=0;
	char **p = NULL;
	p = barr(&p, " zero");
	p = barr(&p, " one");
	p = barr(&p, " two");
	p = barr(&p, " three");
	p = barr(&p, "This is data/four/and more");
	p = barr(&p, " five");
	p = barr(&p, " six");
	p = barr(&p, " seven");
	p = barr(&p, " eight");
	p = barr(&p, " nine");


        /* Example of find and replace the hard way*/
	if ((s = findarr(p,"six",&i)) != NULL)
	  {
	    free(p[i]);
	    p[i]= (char *) malloc(sizeof(char)*30);
	    snprintf(p[i],30,"New Value");
	  }

     
	/* Better example that is easy */
	rarr(&p, "four", "New Four");
	rarr(&p, " nine", "Building on nine\n 1. more"
	     "\n 2. data here"
	     "\n 3. data here"
	     "\n 4. data here"
	     "\n 5. data here"
             );

	prarr(p);
	freearr(&p);

	return 0;

}
