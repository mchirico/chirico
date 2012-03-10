/* Copyright (c) 2005 GPL mchirico@users.sourceforge.net
   http://ftp1.sourceforge.net/cpearls/simple_but_common_cpp.tar.gz

   This is a simple example of RAII or Resource Acquisition is Initialization.
   RAII provides a safe way seize and release resources even in the face
   of exceptions.



*/



#include <iostream>
#include <string>
using namespace std;

class Msg {
public:
  int prt(string s) {
    cout << "This is s in Msg: " << s << endl;
    return 1;
  }
  
};

class MsgHandle {
public:
  explicit MsgHandle( Msg *aMsg ): r_(aMsg) {}
  
  ~MsgHandle() { delete r_; }
  Msg *mptr() { return r_; }
private:
  MsgHandle( const MsgHandle &);
  MsgHandle &operator =( const MsgHandle &);
  Msg *r_;
};

int func1(string s) {
  MsgHandle rh(new Msg);
  
  if (s.size() == 0) /* We can even throw an exception here and be ok*/
    return 0;
  rh.mptr()->prt(s);
  return 1;
}


int main(void){
  func1("sample");

}
  
