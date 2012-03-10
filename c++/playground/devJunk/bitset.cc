#include <bitset>
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
  bitset<1024> b0(string("1000010000001"));
  cout << b0 << endl;
  return 0;
}
