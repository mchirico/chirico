#include "stuff.h"
namespace stuff {
  int a = 34;
}

int stuff::f(int i)
{
  return 3+i;
}
// Note: can be defined outside
int      stuff::b=12;
int      stuff::c=13;
double   stuff::k = 2.3;
