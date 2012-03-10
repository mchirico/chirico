#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;

int main(void)
{

  cout <<"CHAR_BIT " <<  CHAR_BIT << endl;
  cout <<"LONG_MAX " <<  LONG_MAX << endl;
  cout << "ULONG_MAX " << ULONG_MAX << endl;
  return 0;

  /*
On a 64 bit system, you will get the following:

8
9223372036854775807 = pow(2,63)
18446744073709551615 = pow(2,64)

   */
}
