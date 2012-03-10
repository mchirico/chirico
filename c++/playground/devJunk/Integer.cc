#include <iostream>
using std::cout;
using std::endl;

#include "Integer.h"

Integer::Integer(int i):value(i)
{
  cout << "Constructor for Integer " << value << endl;
}

Integer::~Integer()
{
  cout << "Destructor for Integer " << value << endl;
}

void Integer::setInteger(int i)
{
  value = i;
}

int Integer::getInteger() const
{
  return value;
}

