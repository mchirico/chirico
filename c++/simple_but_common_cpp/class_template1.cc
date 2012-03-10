/*
  Copyright GPL 2004 mmc Mike Chirico mchirico@users.sourceforge.net
  Sat May  1 08:11:49 EDT 2004


  Simple program demonstrating how a class can be initialized
  to take any number of containers.
  
  B
   b.a()  Prints contents of container
   b.c(string )  Prints string and size of container.


*/


#include <iostream>
#include <vector>
#include <list>
#include <string>





template <typename T, template <typename> class C>
class B {
public:
  C<T> v;
  void push(T t2) {
    v.push_back(t2);
  }

  void c(std::string s=" ")
  {
    std::cout << s << v.size() << std::endl;

  }

  void a()
  {
    typename C<T>::const_iterator npos;
    for(npos=v.begin() ; npos != v.end(); ++npos)
      std::cout << *npos << " ";

    std::cout << std::endl;

  }

};

using namespace std;
int main()
{
  B<int,vector > b0;
  B<string,vector > b1;
  B<int,list > b2;


  
  b0.push(3);
  b0.push(6);
  b0.a();
  b0.c("Length in b=");



  b1.push("one");
  b1.push("two");
  b1.push("three");
  b1.a();
  b1.c("Length in b1=");

  b2.push(34);
  b2.push(45);
  b2.a();
  b2.c("Length in b2=");

  


  
  

}
