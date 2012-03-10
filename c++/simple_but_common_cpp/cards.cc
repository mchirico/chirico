/* Copyright (c) GPL 2006 by Mike Chirico <mchirico@users.sourceforge.net>


   This is test script for generating Texas Hold'em hands 
   and experimenting with the probability of the game.

   $ ./cards <number of players>


   $ ./cards 8
   Player: 0 Ah,7s <3d,7h,5h,2h,Kc>
   Player: 1 Qc,Td <3d,7h,5h,2h,Kc>
   Player: 2 Kh,4c <3d,7h,5h,2h,Kc>
   Player: 3 8s,7c <3d,7h,5h,2h,Kc>
   Player: 4 Tc,4s <3d,7h,5h,2h,Kc>
   Player: 5 6h,4d <3d,7h,5h,2h,Kc>
   Player: 6 Jc,9c <3d,7h,5h,2h,Kc>
   Player: 7 9s,3c <3d,7h,5h,2h,Kc>




CVS Location:
http://cvs.sourceforge.net/viewcvs.py/cpearls/cpearls/src/posted_on_sf/simple_but_common_cpp/cards.cc


For card odds see
http://www.flopturnriver.com/hand_112603-pot_odds.html
http://www.texasholdem-poker.com/pot_odds_calculator.php
*/


#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <list>
#include <set>
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BUFS 4

/* Generate random seed */

int seed() {
  union U {
    ssize_t mlong;
    char c[4];
   };
  union U u;

  char buf[BUFS+1];
  int fp,n;

  if ((fp = open ("/dev/urandom", O_RDONLY)) == -1)
    {
      fprintf (stderr, "Can't open data: %s\n", strerror (errno));
      return 0;
    }

  if ( ( n=read(fp, buf, BUFS )) >=  4)
    {
      buf[n]='\0';
      u.c[0]=buf[0];
      u.c[1]=buf[1];
      u.c[2]=buf[2];
      u.c[3]=buf[3];

      return u.mlong;

    } else {

      return 0;
    }
  close(fp);



}


class Card {
public:
  void set_value(int i) { value=i; }
  int get_value() const { return value; }

  void set_order(double o) { order=o; }
  double get_order() const { return order; }

private:
  double order;
  int value;
};

class cmp_Card {
public:
    bool operator() (const Card&, const Card&) const;
};

bool cmp_Card::operator()(const Card& x, const Card& y) const
{
    return (x.get_order() < y.get_order());
}


class Cards {
public:
  Cards() {

    /* Seeds based on time are bad for card games.
       So DO NOT use something like the following:
         std::srand(static_cast<unsigned int>(time(NULL)));

       Instead, use the following seed() program.
    */

       std::srand(static_cast<unsigned int>(seed()));
       for(int i=0; i <52; ++i)
	 {
	   c[i].set_value(i);
           c[i].set_order(doubleRand());
           deck.push_back(c[i]);
	 }
       deck.sort(cmp_Card());
       const_iter=deck.begin();
  }

  void shuffle() {
       for(iter=deck.begin(); iter != deck.end(); ++iter)
	 {
           (*iter).set_order(doubleRand());
	 }    
       deck.sort(cmp_Card());
       const_iter=deck.begin();
       /*       for(iter=deck.begin(); iter != deck.end(); ++iter)
	 {
	   std::cout << (*iter).get_value() << std::endl;
	 }
       */
     
  }

  int deal() {

    lastcard=-1;
    if (const_iter!= deck.end())
      {  
	lastcard=const_iter->get_value();
	++const_iter;
      }
    return lastcard;
  }

private:

  Card c[52];
  std::list<Card> deck;
  std::list<Card>::const_iterator const_iter;
  std::list<Card>::iterator iter;

  int lastcard;
  bool shuffled;

  double doubleRand( ) {
     return double(std::rand( )) / (double(RAND_MAX) );
  }
};


class CFace {
public:
  
  std::string value(int i) {
    raw_=i;
    value_= i%13;
    adj_value_ = (value_==0) ? 13: value_; 
    suit_= i/13;
    ss.str("");

    switch(value_) {
    case 0:
      ss << "A";
      break;
    case 9:
      ss << "T";
      break;
    case 10:
      ss << "J";
      break;
    case 11:
      ss << "Q";
      break;
    case 12:
      ss << "K";
      break;
    default:
      ss << (value_+1);
    }

    switch(suit_) {
    case 0:
      ss << "h";
      break;
    case 1:
      ss << "s";
      break;
    case 2:
      ss << "c";
      break;
    case 3:
      ss << "d";
      break;
    }
    return ss.str();
  }

  std::string  fvalue() { return ss.str().substr(0,1); }
  std::string  value() { return ss.str(); }
  std::string  suit() { return ss.str().substr(1,1); }
  int raw() { return raw_; }
  int adjvalue() { return adj_value_; }

private:
  int suit_;
  int value_;
  int adj_value_;
  int raw_;
  std::stringstream ss;
};


class Player {
public:
  Player():num_in_hand(0),state(0) {}
  void pocket(int raw) {
    if (num_in_hand >=2 || num_in_hand < 0 ) 
          { 
            num_in_hand=0; 
	    state=0;
           }
    pocket_[num_in_hand].value(raw);
    num_in_hand++;
    state++;
  }
  void flop(int cards[]) { 
    for(int i=0; i<3; ++i)
      {
      flop_[i].value(cards[i]);
      }
    state++;
  }

  

  void forth(int card) { 
    forth_.value(card);
    state++;
  }
  void river(int card) { 
    river_.value(card);
    state++;
  }

  std::string print() { 
       switch(state) {
       case 1:
            return pocket_[0].value()+","+pocket_[1].value();
            break;
       case 2:
            return pocket_[0].value()+","+pocket_[1].value();
            break;
       case 3:
            return pocket_[0].value()+","+pocket_[1].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+">";
            break;
       case 4:
            return pocket_[0].value()+","+pocket_[1].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+","
                   + forth_.value()+">";
            break;
       case 5:
            return pocket_[0].value()+","+pocket_[1].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+","
    	  + forth_.value()+","+river_.value()+">";
            break;
       }
    
           return pocket_[0].value()+","+pocket_[1].value();
    
  }


  /* This is the eval hand engine
   */

  std::string eval(int i) {
    // i  0- eval pocket, 1- pocket+flop, 2- pocket+flop+river etc.

    std::list<std::string> crd;

     std::stringstream ss;
     int multiple=1;
     int value=0;
     i=0; //Not used yet
     ss.str("");


     



     ss << " Pocket [";

     if (abs(pocket_[0].adjvalue() - pocket_[1].adjvalue()) == 1)
       {  multiple=4; 
       ss << "straight ";
       }

     if ( (pocket_[0].adjvalue() >= 9) && (pocket_[1].adjvalue() >= 9) )
       {  multiple=multiple+2; 
       ss << "bhigh ";
       }
     else  if ( (pocket_[0].adjvalue() >= 9) || (pocket_[1].adjvalue() >= 9) )
       {  multiple=multiple+1; 
       ss << "high ";
       }


     if (pocket_[0].suit() == pocket_[1].suit())
       {  multiple = multiple+1; 
       ss << "flush ";
       }

     if (pocket_[0].fvalue() == pocket_[1].fvalue())
       {  multiple=10; 
       ss << "pair ";
       }

     value=(pocket_[0].adjvalue()+pocket_[1].adjvalue())*multiple;

     ss << value;
     ss << "]";


     ss << "\t";
     for(int i=0; i<2; ++i)
       {
        crd.push_back(pocket_[i].fvalue());
       }


     for(int i=0; i<3; ++i)
       {
        crd.push_back(flop_[i].fvalue());
       }

     crd.sort();

     std::string delim="";
     for(std::list<std::string>::const_iterator cl(crd.begin()); cl!=crd.end(); ++cl)
       {
	 ss << delim << *cl; 
         delim=",";
       }


     return ss.str();

  }



  std::string oprint() { 
       switch(state) {
       case 1:
	 if (pocket_[0].adjvalue() > pocket_[1].adjvalue()) 
            return pocket_[0].value()+","+pocket_[1].value();
         else
            return pocket_[1].value()+","+pocket_[0].value();
            break;
       case 2:
	 if (pocket_[0].adjvalue() > pocket_[1].adjvalue()) 
            return pocket_[0].value()+","+pocket_[1].value();
         else
            return pocket_[1].value()+","+pocket_[0].value();
            break;
       case 3:
	 if (pocket_[0].adjvalue() > pocket_[1].adjvalue()) 
            return pocket_[0].value()+","+pocket_[1].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+">";
         else
	   return pocket_[1].value()+","+pocket_[0].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+">";
            break;
       case 4:
	 if (pocket_[0].adjvalue() > pocket_[1].adjvalue()) 
            return pocket_[0].value()+","+pocket_[1].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+","
	    + forth_.value()+">";
         else
            return pocket_[1].value()+","+pocket_[0].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+","
                   + forth_.value()+">";
            break;
       case 5:
	 if (pocket_[0].adjvalue() > pocket_[1].adjvalue()) 
            return pocket_[0].value()+","+pocket_[1].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+","
	      + forth_.value()+","+river_.value()+">" +eval(0);
         else
            return pocket_[1].value()+","+pocket_[0].value()+" <"+flop_[0].value()+","+flop_[1].value()+","+flop_[2].value()+","
    	  + forth_.value()+","+river_.value()+">"+eval(0) ;

            break;
       }
    
           return pocket_[0].value()+","+pocket_[1].value();
    
  }




  std::string get_pocket_value(int i) {
    if(i<=1 && i >=0)
      return pocket_[i].value();
  }

  std::string get_pocket_fvalue(int i) {
    if(i<=1 && i >=0)
      return pocket_[i].fvalue();
  }

  std::string get_pocket_suit(int i) {
    if(i<=1 && i >=0)
      return pocket_[i].suit();
  }

  std::string get_flop_value(int i) {
    if(i<=2 && i >=0)
      return flop_[i].value();
  }

  std::string get_flop_fvalue(int i) {
    if(i<=2 && i >=0)
      return flop_[i].fvalue();
  }

  std::string get_flop_suit(int i) {
    if(i<=2 && i >=0)
      return flop_[i].suit();
  }

  std::string get_forth_value() {
      return forth_.value();
  }

  std::string get_forth_fvalue() {
      return forth_.fvalue();
  }

  std::string get_forth_suit() {
      return forth_.suit();
  }


  std::string get_river_value() {
      return river_.value();
  }

  std::string get_river_fvalue() {
      return river_.fvalue();
  }

  std::string get_river_suit() {
      return river_.suit();
  }


 
private:
  CFace pocket_[2];
  CFace flop_[3];
  CFace forth_;
  CFace river_;
  int num_in_hand;
  int state;

};

void evalhands(Player p[],int players)
{
     for(int i=0; i<players; ++i)
       {
        std::cout << "Player: " << i << " " << p[i].oprint() << std::endl;
       }  

}




int main(int argc, char **argv ) {

  int players=6;
  Cards C;
  CFace CF;
  C.shuffle();
  Player p[23];
  int card,flop[3],forth,river;
  int count=0;
  long stat=0;


  if(argc==2)
    players=atoi(argv[1]);

  if(players <=1 || players >= 22)
    players=6;


  while(++stat < 2)
    {
     while( ((card = C.deal()) != -1)  && ++count <= (players*2))
      {
	       p[count%players].pocket(card);
      }


     C.deal(); // burn 
     flop[0]=C.deal(); // turn
     flop[1]=C.deal();
     flop[2]=C.deal();
     for(int i=0; i<players; ++i)
       {
         p[i].flop(flop);
       }
     C.deal(); // burn 
     forth=C.deal();
     for(int i=0; i<players; ++i)
       {
         p[i].forth(forth);
       }

     C.deal(); // burn 
     river=C.deal();
     for(int i=0; i<players; ++i)
       {
         p[i].river(river);
       }

       evalhands(p,players);

     count=0;
     C.shuffle();
    }


  return 0;
}
