#include <iostream>
#include <iterator>
#include <vector>
using namespace std;


int main(void)
{
  int* p;
  int* p2;
  vector<int>::iterator vi1;
  vector<int>::iterator vi2;

  int k[10];
  vector<int> v;

  k[3]=5;
  k[5]=2;

  v.push_back(30);
  v.push_back(50);

  vi1=v.begin();
  vi2=v.begin();
  ++vi2;


  p=&k[3];
  p2=&k[5];


  std::cout << "This program demonstrates how swap(), from <iterator> can be used" << std::endl;
  std::cout << "for swapping points like \"int* p\" and iterators like \"vector<int>::iterator\" \n\n" << std::endl;

  std::cout << " This is the pointer example *p and *p2:\n" << std::endl;  
  std::cout << *p << std::endl;
  std::cout << *p2 << std::endl;

  std::cout << "Now calling swap(p,p2) " << std::endl;
  swap(p,p2);

  std::cout << *p << std::endl;
  std::cout << *p2 << std::endl;

  std::cout << "\n This is the vector example vi1 and vi2:\n" << std::endl;  
  std::cout << *vi1 << std::endl;
  std::cout << *vi2 << std::endl;
  std::cout << "Now calling swap(vi1,vi2) " << std::endl;
  swap(vi1,vi2);
  std::cout << *vi1 << std::endl;
  std::cout << *vi2 << std::endl;







  return 0;

}

