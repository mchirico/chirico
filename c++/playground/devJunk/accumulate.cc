#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>


template< typename T >
class SumSquaresClass: public std::binary_function<  T, T, T>
{
public:
  T operator() (const T &total, const T &value)
  {
    return total + value*value;
  }
};

int main(void)
{

  std::vector< int > integers;
  std::ostream_iterator< int > output( cout, " " );
  std::ostream_iterator< int > outputE( cerr, " " );


  for(int i=0; i<=500;++i)
    integers.push_back(i);

  cout << "vector integers contains:\n";
  std::copy(integers.begin(), integers.end(), output);

  int result = std::accumulate(integers.begin(), integers.end(), 0, SumSquaresClass< int > ());

  cout << endl << endl << "Result " << result << endl;



}
