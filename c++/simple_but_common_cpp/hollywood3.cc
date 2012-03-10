/* Copyright (c) GPL Mike Chirico mchirico@users.sourceforge.net mchirico@comcast.net 
 
   This is my version of Item 19 in Dewhurst's "C++ Common Knowledge".
   but it is also combined with RAII. Compare this to hollywood1 which
   requires a few extra delete statements.
    http://www.semantics.org/commonknowledge/index.html


   The only difference between hollywood2.cc and hollywood2.cc is that 
   this version call onClick2();

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


class Action {
public:
  virtual ~Action()=0;
  virtual void operator()() = 0;
  virtual int mdo() = 0;
  virtual Action *clone() const = 0;
};

// Note difference between Action() and Action(){}
// Since it is a pure virtual function it must be
// declared outside of Action 
Action::~Action(){}

class Button {
public:
  Button( const std::string &label )
    : label_(label), action_(0) {}
  void setAction( const Action *newAction ) {
    Action *temp = newAction->clone();
    delete action_;
    action_ = temp;
  }
  void onClick() const
  { if( action_ ) (*action_)(); }

  void onClick2() const
  { if( action_ ) action_->mdo(); }


  ~Button() { 
      if (action_){
            delete action_;
            action_ = 0;
        }
  }
private:
  std::string label_;
  Action *action_;
};


class PlayMusic : public Action {
public:
  PlayMusic( const std::string &songFile )
    : song_(songFile) {}
  void operator()() { std::cout << "Class: PlayMusic  Song:" << song_ << std::endl;}
  int mdo() { 
           std::cout << "We are in mdo PlayMusic" << std::endl;
           return 3; 
            }
  PlayMusic *clone() const
     { return new PlayMusic(*this); }
private:
  std::string song_;
};


class PlayMusic2 : public Action {
public:
  PlayMusic2( const std::string &songFile )
    : song_(songFile) {}
  void operator()() { std::cout << "Class: PlayMusic2  Song:" << song_ << std::endl;}
  int mdo() { 

    std::cout << "Ok more here" << std::endl;
              return 3; 
              }
  PlayMusic2 *clone() const
     { return new PlayMusic2(*this); }
private:
  std::string song_;
};



int main(void)
{

 ResourceHandle<Button> b(new Button (" Anoko no namaewa"));
 ResourceHandle<Action> rh0( new PlayMusic( "AnokoNoNamaewa.mp3"));
 ResourceHandle<Action> rh1( new PlayMusic2( "3 Dog Nights Best Hits.mp3"));

 std::cout << "\n\nCallback Example (Item 19,40) in Dewhurst, \"C++ Common Knowledge\" " << std::endl;  
 std::cout << "  This  example is done with  RAII.\n" << std::endl; 

 b.get()->setAction( rh0.get() );
 b.get()->onClick();
 b.get()->onClick2();
 b.get()->setAction( rh1.get() );
 b.get()->onClick();


}
