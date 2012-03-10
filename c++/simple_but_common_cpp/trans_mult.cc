#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <string>
#include <list>
#include <vector>


using namespace std;
int main(void)
{
  vector<double> v;
  vector<double> m;
  vector<double> res;

  m.push_back(1);
  m.push_back(10);
  m.push_back(100);

  v.push_back(34);
  v.push_back(23);
  v.push_back(55);

  transform(v.begin(),v.end(),m.begin(),back_inserter(res),multiplies<double>());
       copy(v.begin(),v.end(),ostream_iterator<double>(cout,"\n"));
       copy(res.begin(),res.end(),ostream_iterator<double>(cout,"\n"));
}
