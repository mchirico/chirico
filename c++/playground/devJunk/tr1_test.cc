/*
   g++ tr1_test.cc -o tr1_test
*/

#include<tr1/array>
#include<iostream>
 
int main()
{
  std::tr1::array<int, 5> a = {{ 1,2,3,4,5 }};
  std::cout <<a[3] <<'\n';
}
