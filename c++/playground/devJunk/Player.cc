#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Player {
public:
  Player(const char* name, int rating, int rclass)
    : name_(name), rating_(rating),class_(rclass)
  { }
  const char* getName() { return name_; }
  int getRating() { return rating_; }
  int getClass() { return class_; }

private:
  const char* name_;
  int rating_;
  int class_;
};


struct IsWeakerPlayer {
  bool operator( )(Player& x, Player& y) {
    if (x.getClass() < y.getClass())
	   return x.getClass() < y.getClass();
    return x.getRating() < y.getRating();

  }
  };

int main( )
{
  Player kasparov("Garry Kasparov", 2805,0);
  Player anand("Viswanathan Anand ", 2788,1);
  Player topalov("Veselin Topalov", 2788,3);
  vector<Player> v;



  v.push_back(kasparov);
  v.push_back(anand);
  v.push_back(topalov);
  cout << "the best player is ";
  cout << max_element(v.begin( ), v.end( ), IsWeakerPlayer( ))->getName();
  cout << endl; 
}
