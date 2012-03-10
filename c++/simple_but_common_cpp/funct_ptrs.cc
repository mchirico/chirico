#include <iostream>

int f(int a)
{
  return 5+a;
}


int b (int a)
{
  return 3+a;
}

int main(void)
{
  typedef  int (*fp)(int) ;
  fp t[3];


  t[0]=&f; 
  t[1]=b;

  std::cout << t[0](3) << std::endl;
  std::cout << t[1](3) << std::endl;


}
