#include <cstdlib>
#include <ctime>
#include <iostream>



double doubleRand( ) {
  return double(std::rand( )) / (double(RAND_MAX) );
}

int main( ) {


  std::srand(static_cast<unsigned int>(time(NULL)));
  std::cout << "Expect 5 numbers within the interval [0,1]" << std::endl;
  for(int i=0; i<5; ++i) {
    std::cout <<  doubleRand() << std::endl;
  }

  return 0;
}
