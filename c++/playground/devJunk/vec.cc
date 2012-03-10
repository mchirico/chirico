#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
  vector< vector<int> > m;
  vector<int> v;
  vector<int> v2;

  for(int i=0;i<23; ++i)
    v.push_back(i);

  for(int i=0;i>-22; --i)
    v2.push_back(i);


  m.push_back(v);
  m.push_back(v2);

  cout << m.at(1).at(13) << endl;

}

