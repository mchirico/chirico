/* Copyright (c) GPL Mike Chirico mchirico@users.sourceforge.net mchirico@comcast.net 
 
   This is my version of Item 19 in Dewhurst's "C++ Common Knowledge".
    http://www.semantics.org/commonknowledge/index.html


*/

#include <iostream>
#include <string>

class Action {
public:
  virtual ~Action()=0;
  virtual void operator()() = 0;
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
    if ( action_ ) delete action_;
    action_ = temp;
  }
  void onClick() const
  { if( action_ ) (*action_)(); }

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
  PlayMusic2 *clone() const
     { return new PlayMusic2(*this); }
private:
  std::string song_;
};


int main(void)
{
 Button *b = new Button (" Anoko no namaewa");
 PlayMusic *song =  new PlayMusic( "AnokoNoNamaewa.mp3");
 PlayMusic2 *song2 =  new PlayMusic2( "3 Dog Nights Best Hits.mp3");

 std::cout << "\n\nCallback Example (Item 19) in Dewhurst, \"C++ Common Knowledge\" " << std::endl;  
 std::cout << "  See \"hollywood2.cc\" for example with RAII.\n" << std::endl; 

 b->setAction( song );
 b->onClick();
 b->setAction( song2 );
 b->onClick();
 delete song;
 delete b;
}
    
