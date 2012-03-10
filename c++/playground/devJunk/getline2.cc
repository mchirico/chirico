#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>

using namespace std;

int main(void)
{
  string s;
  vector< string > v;

  
  cout << "Enter line:" << endl;
  while (getline(cin,s))
    {
      v.push_back(s);
    }

  copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
}
