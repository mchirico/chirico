#include<iostream>
#include<tr1/tuple>
using namespace std;
using namespace std::tr1;

int main()
{
  // std::tr1::tuple<int, std::string, double> t(12,"Hello", 43.56);
  // std::cout<<std::tr1::get<1>(t)<<std::endl;


  tuple<int, string, double> t(12,"Hello", 43.56);
  cout<<get<1>(t)<< endl;
}
