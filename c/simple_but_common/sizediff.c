/* Reference Sutter: "Exceptional C++ Style
    40 New Engineering Puzzles, Programming
    Problems, and Solutions"

    Order makes a difference.

*/

#include <stdlib.h>
#include <stdio.h>

struct X1 {
  char c1;
  long l;
  char c2;
};

struct X2 {
  long l;
  char c1;
  char c2;
};

struct X3 {
  char c1;
  double d;
  char c2;
  long l;
};

struct X4 {
  char c1;
  char c2;
  double d;
  long l;
};

int main(void)
{
  printf("sizeof(X1) = %d\n",sizeof(struct X1));
  printf("sizeof(X2) = %d\n",sizeof(struct X2));
  printf("sizeof(X3) = %d\n",sizeof(struct X3));
  printf("sizeof(X4) = %d\n",sizeof(struct X4));

  return 0;

}
