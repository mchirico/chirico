#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "DivideByZeroException.h"

double quotient(int numerator, int denominator)
{
  if (denominator == 0)
    throw DivideByZeroException();

  return static_cast< double > ( numerator ) /denominator;

}

int main(void)
{
  int number1;
  int number2;

  double result;

  try 
    {
      result = quotient(number1, number2);
    }
  catch( DivideByZeroException &divideByZeroException )
    {
      cout << "-->" << divideByZeroException.what() << "<--" << endl;
    }


  return 0;
}
