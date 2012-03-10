#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::auto_ptr;

#include "Integer.h"




int main(void)
{
  auto_ptr< Integer > pI( new Integer(3));

  cout << "pI " << (*pI).getInteger() << endl;
  pI->setInteger(34);
  cout << "pI " << (*pI).getInteger() << endl;
 

  return 0;
}
