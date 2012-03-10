#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

/* Take a look at the following paper:
    http://www.research.att.com/~bs/DnE2005.pdf
*/

template<class Iter, class T> Iter myfind(Iter first, Iter last, const T& val)
{
  while(first!=last && *first!=val) ++first;
  return first;
}



int main(void)
{


  vector<int> v;
  list<string> s;

  v.push_back(3);
  v.push_back(5);
  v.push_back(16);
  v.push_back(4);

  vector<int>::iterator vi = find(v.begin(),v.end(),4);
  if (vi != v.end())
    cout << "test here" << *vi << endl;

  vector<int>::iterator vi2 = myfind(v.begin(),v.end(),4);
  if (vi2 != v.end())
    cout << "test here" << *vi2 << endl;
}
