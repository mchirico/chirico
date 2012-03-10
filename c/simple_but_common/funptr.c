#include <stdio.h>
#include <stdlib.h>

double Plus (double a, double b) { return a+b; }
double Mult (double a, double b) { return a*b; }
double Minus (double a, double b) { return a-b; }
double Div (double a, double b) { return a/b; }

void SF(double a, double b, double (*ptF)(double, double))
{
  double result = ptF(a,b);
  printf("%lf\n",result);
}
int main()
{
  SF(10,23,&Plus);
  SF(10,23,&Mult);
  SF(10,23,&Minus);
  return 0;

}
