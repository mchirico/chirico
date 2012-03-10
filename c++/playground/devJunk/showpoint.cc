#include <iostream>
using std::cout;
using std::endl;
using std::showpoint;

int main(void)
{
  cout << "No showpoint" << endl;
  cout << 1.0 << endl 
       << 1 << endl 
       << 2.34 << endl;


  cout << endl << "With showpoint" << endl;
  cout << showpoint << 1.0 << endl 
       << 1 << endl 
       << 2.34 << endl;


  return 0;
}

   
