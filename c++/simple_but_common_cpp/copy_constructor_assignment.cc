/* Copy_constructor_assignment.cc
   Copyright (c) 2004 GPL Mike Chirico, mchirico@comcast.net or mchirico@users.sourceforge.net

   Reference: "The C++ Programming Language", 3rd ed, by Stroustrup 
   pg. 246.
  

   Download:
   http://prdownloads.sourceforge.net/cpearls/simple_but_common.tar.gz?download

*/


#include <iostream>


class Name {
public:
  char* s;
};


class Table {
  Name *p;
  size_t sz;
public:
  Table(size_t s=15) { 
            p = new Name[sz=s];
            for(size_t i=0; i< sz; ++i) p[i].s="****";
                       }
  Table(const Table &t);
  Table& operator=(const Table&);
  int prt();
  void asgn(char* ts,size_t index);
  ~Table(){ delete[] p; }  
};



Table& Table::operator=(const Table &t)
{
  if( this != &t) {
    delete[] p;
    p = new Name[sz=t.sz];
    for(size_t i=0; i< t.sz; ++i) p[i]=t.p[i];
  }
  return *this;
}

int Table::prt()
{
  for(size_t i=0; i< sz; ++i) std::cout << p[i].s << " ";
  std::cout << std::endl;
  return 0;
}

/*
  asgn will increase the array of strings, if needed
  to size index+1, and add the string ts to position
  index.
*/
void Table::asgn(char* ts,size_t index)
{
  if(index < sz ) { 
     p[index].s=ts;
  }else if ( index >= sz ){
     Name *tp;
     tp=p;

     p = new Name[index+1];

     for(size_t i=0; i< sz; ++i) p[i].s=tp[i].s;
     delete [] tp;
     for(size_t i=sz; i < index; ++i)p[i].s="****";

     p[index].s=ts;
     sz=index+1;
    }
      
}



int main(void)
{

  Table t1;
  Table t2(5);

  // this is bigger than initial sz
  t1.asgn("myname",20);
  t1.prt();
  t2.prt();




  t1=t2;

  t1.prt();
  t2.prt();
}
