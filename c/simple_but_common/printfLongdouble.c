#include "stdio.h"
int main (int argc, char *argv[])
{
  long double d = 123456789.0123456789;
  printf("%10.10Lf\n", d);
  return(0);
}
