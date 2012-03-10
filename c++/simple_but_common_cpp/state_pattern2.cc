/* Copyright (C) 2007 GPL  Mike Chirico mmc mchirico@users.sourceforge.net

  State Design Pattern

  Object:

     Several objects need to share a common state.

   You may first want to look over state_pattern.cc. This 
   version builds on the first.

*/




#include <iostream>

class State
{
public:
  State(int state=0): _state(state),count_changes(0) {}
  void set_state(int state){
    _state=state;
    count_changes++;
  }
  void inc(){
    _state++;
    count_changes++;
  }
  int get_state() {
    std::cout << "state = " << _state << std::endl;
    return _state;
  }
  int num_state_changes(){
    std::cout << "Number State Changes = " << count_changes << std::endl;
    return count_changes;
  }
private:
  int _state;
  int count_changes;
};


class Obj_base
{
public:

  Obj_base() {}
  virtual ~Obj_base() {}

  Obj_base& inc() {
    _state().inc();
      return *this;
  }

  Obj_base& set_state(int i) {
    _state().set_state(i);
      return *this;
  }

  int get_state() {
    return _state().get_state();
  }

  int num_state_changes() {
    return _state().num_state_changes();
  }

private:
  State& _state()
  {
    static State _state;
    return _state;
  }
};


class Obj_0: public Obj_base {
};

class Obj_1: public Obj_base {
};

class Obj_2: public Obj_base {
};





int main(void)
{

  Obj_0 object_zero;
  Obj_1 object_one;
  Obj_2 object_two;

  object_zero.set_state(3);
  object_one.get_state();
  object_two.inc();

  object_one.get_state();
  object_one.num_state_changes();
  
  object_zero.set_state(30).inc();
  object_one.num_state_changes();
}
