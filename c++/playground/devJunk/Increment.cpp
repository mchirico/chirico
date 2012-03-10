#include <iostream>
using std::cout;
using std::endl;

#include "Increment.h"

Increment::Increment(int c, int i)
        : count(c), increment(i) {}


void Increment::pr() const
{
    cout << "count = " << count << ", increment = " << increment
    << endl;
}
