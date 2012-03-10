#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  vector<int> v1;
  vector<int> v2;

  int i=3,j=10;

  v2.push_back(5);
  v2.push_back(8);
  v2.push_back(12);
  v2.push_back(19);

  // Assigns the second half - it's a copy
  v1.assign(v2.begin()+v2.size()/2,v2.end());
  for( vector<int>::iterator iter=v1.begin(); iter != v1.end();++iter)
    cout << *iter << endl;

  v1.clear();
  v2.clear();

  return 0;
}
