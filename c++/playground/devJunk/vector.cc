#include <iostream>
using std::cout;
using std::endl;
using std::ios;


#include <vector>
using std::vector;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iterator>
using std::istream_iterator;


#include <algorithm>
using std::remove;
//using namespace std;

int main(void)
{
  ifstream dataFile("ints.dat",ios::in);
  // Note the second parens in this. It is very important.
  vector<int> data((istream_iterator<int>(dataFile)),
				 istream_iterator<int>());

  cout << "sizeof vector " << data.size() << endl;

  //data.sort();
  data.erase(remove(data.begin(),data.end(),23), data.end());
  for(vector<int>::const_iterator iter = data.begin(); iter != data.end(); ++iter)
    cout << *iter << endl;


  return 0;
}
