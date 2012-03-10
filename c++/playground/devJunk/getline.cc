#include <iostream>
using namespace std;

int main(void)
{
  const int SIZE = 512;
  char buf[SIZE];

  cout << "Enter line [" << SIZE << "] characters or less:" << endl;
  cin.getline(buf,SIZE);

  cout << "\nThe line:->" << buf << "<-\n";
}
