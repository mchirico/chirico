#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
using namespace std;

unsigned long long sumSquares(unsigned long long total, unsigned long long value)
{
  return total+value*value;
}
template<typename T>
class SumSquaresClass: public std::binary_function<T,T,T>
{
public:
  T operator() (const T &total, const T &value )
  {
    return total + value * value;
  }
};


int main(void)
{

  std::vector< int > v;
  for(int i=0; i<100; ++i)
    v.push_back(i);
   std::ostream_iterator< int > output( cout, "\n");

  cout << " \n";
  // copy(v.begin(), v.end(), output);
  unsigned long long result = std::accumulate(v.begin(), v.end(), 0, SumSquaresClass< int >());
  cout << "\n\n" << result;
  return 0;
}
