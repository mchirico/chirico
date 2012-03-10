/* Copyright (c) 2005 GPL Mike Chirico mchirico@users.sourceforge.net or mchirico@comcast.net

 This is an example of creating a string class from char.



 Download:
   http://prdownloads.sourceforge.net/cpearls/simple_but_common_cpp.tar.gz?download

*/
#include <iostream>
#include <string.h>

class S {

public:

  S(const char *str){
   if (!str) str="";
   s_ = new char[ strlen(str)+1];
   strcpy(s_,str);
  }

  const S& operator()(const char *str) {
      if(!str) str="";
      char *tmp = strcpy(new char[ strlen(str)+1],str);
      delete []  s_;
      s_=tmp;
   return *this;
  }

  const S& operator=(const char *str) {
     if(!str) str="";
     char *tmp = strcpy(new char[ strlen(str)+1],str);
     delete [] s_;
     s_=tmp;
     size_m=strlen(s_);
     return *this;
   }

  const S& operator+=(const char *str) {


     if(!str) str="";
     char *tmp = strcpy(new char[ strlen(str)+strlen(s_)+1],s_);
     tmp =strcat(tmp,str);
     delete [] s_;
     s_=tmp;
     return *this;
   }

  void p() { std::cout << s_ << std::endl; }

private:
  char *s_;
  int size_m;
};


int main(void)
{
  S x("one");
  S y("two");
  x.p();
  x = y("more");
  x +=" 123456789";
  x.p();

}
