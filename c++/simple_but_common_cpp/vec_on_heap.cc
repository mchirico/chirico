/*  Example of putting objects on the
    heap

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> t(const string& s,const int k)
{
  vector<string> mt;

  mt.push_back(s);
  for(int i=0; i<k; ++i)
   mt.push_back("more ");
  return mt;
}
int main(void)
{
  vector<string> v=t("test",5);

  
  for(unsigned int i=0; i< v.size(); ++i)
      cout << v[i] << endl;



  return 0;
}
