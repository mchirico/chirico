#include <stdlib.h>
#include <stdio.h>

union U {
  double value;
  char name[10];
};

int main(void) {

  union U u;
  fprintf(stderr,"sizeof(u)=%ld sizeof(double)=%ld, sizeof(name[10])\n",
	  sizeof(u),sizeof(double));
  return 0;

}
