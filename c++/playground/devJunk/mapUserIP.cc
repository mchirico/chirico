#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <map>



typedef std::map< std::string, long, std::less< string > > H;

int main()
{
  H h;
  string ipu="192.168.2.34:chirico";
  h.insert(H::value_type(ipu,1));


  ipu="192.158.2.3:root";
  H::const_iterator result = h.find(ipu);
  if (result != h.end()){
    h[ipu]+=1;
  } else {
    h[ipu]=1;
  }

  for(H::const_iterator iter = h.begin();
      iter != h.end(); ++iter )
    cout << iter->first << '\t' << iter->second << '\n';

  return 0;
}
