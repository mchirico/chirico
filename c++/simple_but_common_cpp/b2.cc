/* Copyright (C) 2005 GPL mchirico@users.sourceforge.net

   Example of using virtual keyword, where is does seem to matter.

   C++ Common Knowledge, Stephen C. Dewhurst, Pg 231.

   States that virtual keyword is optional; however, this is incorrect
   with the current version of gcc.


*/

#include <iostream>


class A {
public:
  /* You need virtual here so that A::p() will not always be called.
     Try taking only the keyword virtual out below. to confirm       */
  virtual A& p() { 
                   fprintf(stderr,"A::a_ = %d\n",a_); 
                   return *this; 
                 }

  A& setA(int a=0) { a_=a;
                     return *this; 
                     }

  int getA() { return a_; }

  virtual ~A() {};

private:
  int a_;

};

class B: public A {


public:
  B(int a=3): a_(a) { A::setA(a); }

  ~B() { A::setA(0); }
  B& p() {  

        fprintf(stderr,"We are in b %d\n",A::getA());
        if ( A::getA() < 10 )
	   { 	     A::p();  } 
	 else {  fprintf(stderr,"this is b\n"); }

          return *this; 
          }
private:

  int a_;


};

int main(void)
{
  B *b = new B();

  /* The virtual keyword makes a difference only when called in 
     this succession */
  b->setA(5).p().setA(11).p();
  b->p();

  delete b;
}
