/*
  Simple sample of enumeration cycling.  This
  can also be used with dates { mon,tue,wed ...sun)

  An initial class variable can only be a static const int
  or an enum.  All other options must be defined in the
  constructor.

*/

#include <iostream>
using namespace std;
enum Num { zero,one,two,three,four,five,six,seven,eight,nine};
Num& operator++(Num& n)
{
  return  n =  (nine==n)? zero: Num(n+1);
}




void p(Num& n)
{
  cout << n << endl;
}

int main()
{
  Num k;
  k=zero;
  p(k);
  for(int i=0; i < 15; ++i)
   p(++k);

}
