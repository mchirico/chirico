#include <iostream>
using std::cout;


#include "Increment.h"

int main()
{
  Increment value (10,5);
  value.pr();
  value.addIncrement();
  value.pr();

}
