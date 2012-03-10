/* Copyright (c) GPL Mike Chirico mchirico@users.sourceforge.net mchirico@comcast.net 
 
   This program is very similiar to raii.c. Also take a look at the hollywood
   programs.

*/


#include <iostream>
#include <string>



template <typename T>
class ResourceHandle {
public:
  explicit ResourceHandle( T *aResource )
    : r_(aResource) {}
  ~ResourceHandle()
  { delete r_; }
  T *get()
  { return r_; }
private:
  ResourceHandle( const ResourceHandle &);
  ResourceHandle &operator = (const ResourceHandle & );
  T *r_;
};



class A {
 public:
  A(std::string s="Empty", int i=0):s_(s),i_(i) 
           { std::cout << "A was created. s_ = " << s_ 
	    << " i_ = " << i_ << std::endl; }
  ~A() { std::cout << "A was destroyed  s_ = " << s_ << 
      " i_ = " << i_ << std::endl; }

  std::string gets_() { return s_; }
  std::string sets_(std::string s) { s_ = s; return s_; }

  int geti_() { return i_; }
  int seti_(int i) 
        { 
	  i_ = i;
          return i_;
	}
  void printA() { 
            std::cout << "s_ = " << s_ 
	    << " i_ = " << i_ << std::endl; 
            }
private:
  std::string s_;
  int i_;
};





int main(void)
{

 ResourceHandle<A> b(new A ("Initial value of A"));

 b.get()->printA();
 b.get()->seti_(5);
 b.get()->sets_("This is something new.");
 b.get()->printA();



}
