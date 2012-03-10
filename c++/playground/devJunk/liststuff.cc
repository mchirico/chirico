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


#include <algorithm>
using std::remove;
//using namespace std;


int main(void)
{

  ifstream dataFile("ints.dat",ios::in);
  ifstream dataFile2("ints2.dat",ios::in);
  list<int> data ((istream_iterator<int>(dataFile)),
		    istream_iterator<int>());
  list<int> data2 ((istream_iterator<int>(dataFile2)),
		    istream_iterator<int>());

  data.splice(data.end(),data2,
	      find(data2.begin(), data2.end(),23),
              find(data2.rbegin(), data2.rend(),1).base());

  for(list<int>::const_iterator iter = data.begin(); iter != data.end(); ++iter)
    cout << *iter << endl;

}

