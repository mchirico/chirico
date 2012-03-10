/*
  This is an example where, after the main program ends, two
  functions that were initialized at the beginning are run.

  So below, exit_1 and exit_2 run after the main program
  is complete.

  Reference: Advanced Programming in the UNIX® Environment: Second Edition
            Section 7.3  

*/
#include <stdlib.h>
#include <stdio.h>


static void
exit_1(void)
{
  fprintf(stderr,"exit_1\n");
}

static void
exit_2(void)
{
  fprintf(stderr,"exit_2\n");
}

int main(void)
{

  if(atexit(exit_1) != 0)
    fprintf(stderr,"error at atexit(exit_1)\n");

  if(atexit(exit_2) != 0)
    fprintf(stderr,"error at atexit(exit_2)\n");


  fprintf(stderr,"Main immediately before last return\n");
  return(0);
}
