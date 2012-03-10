#include <iostream>
#include <assert.h>

using namespace std;
/*

For debugging:
  g++ -o myassert myassert.cc

To turn off debugging:
  g++ -DNDEBUG -o myassert myassert.cc

*/
int main()
{
  int i;
  cout << "This is an example of using assert for range checking " << endl;
  cout << "For debugging:\n  g++ -o myassert myassert.cc" << endl;
  cout << "To turn off debugging:\n  g++ -DNDEBUG -o myassert myassert.cc" << endl;
  cout << "To turn off debugging:\n  g++ -DNDEBUG -o myassert myassert.cc" << endl << endl;
  cout << "To test enter a number < than zero; The program should abort. " << endl;
  cout << "Next try entering a number >  than zero. The program should run. " << endl << endl;

  cout << "Enter an integer between -10 and 10: ";
  cin >> i;
  assert(i > 0); // Check to see if true, abort if not
  assert(i < 300); // We don't want to go on forever.
  cout << endl;
  for(int k=0; k < i; ++k)
    cout<< "-";

  cout<<endl;
  
  
}
