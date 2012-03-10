#include <iostream>
using std::cout;
using std::endl;

#include <map>

typedef std::map< long, double, std::less< long > > H;

int main()
{
  H h;
  h.insert(H::value_type(15,8));
  h.insert(H::value_type(5,12.8));
  h.insert(H::value_type(21,3.2));
  for(int i=200; i<256; ++i)
    h[i]=i*i/3.0;

  for(H::const_iterator iter = h.begin();
      iter != h.end(); ++iter )
    cout << iter->first << '\t' << iter->second << '\n';

}
