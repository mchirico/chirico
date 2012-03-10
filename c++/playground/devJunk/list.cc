#include <iostream>
using std::cout;
using std::endl;
using std::ios;


#include <list>
using std::list;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iterator>
using std::istream_iterator;

//using namespace std;

int main(void)
{
  ifstream dataFile("ints.dat",ios::in);
  // Note the second parens in this. It is very important.
  list<int> data((istream_iterator<int>(dataFile)),
				 istream_iterator<int>());

  cout << "sizeof list " << data.size() << endl;

  data.sort();
  for(list<int>::const_iterator iter = data.begin(); iter != data.end(); ++iter)
    cout << *iter << endl;


  return 0;
}
