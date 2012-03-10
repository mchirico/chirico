#include<stdarg.h>
#include<stdio.h>

void sum(char *, int, ...);

int main(void)
{
  /* Note: first 5 is number of arguments */
  sum("The sum of 1+2+3+4+5 is %ld.\n",5,1,2,3,4,5);
  return 0;
}

void sum(char *string, int num_args, ...)
{
  int sum=0;
  va_list ap;
  int i;

  va_start(ap,num_args);
  for(i=0;i<num_args;++i)
    {
    sum+=va_arg(ap,int);
    fprintf(stderr,"sum=%d\n",sum);
    }

  printf(string,sum);
  va_end(ap);
}
