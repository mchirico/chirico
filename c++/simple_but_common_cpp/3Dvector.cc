#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(void)
{

  typedef std::vector<int> V1;
  typedef std::vector<V1> V2;
  typedef std::vector<V2> V3;

  typedef std::vector<string> Vs1;
  typedef std::vector<Vs1> Vs2;
  typedef std::vector<Vs2> Vs3;



   V3  v(10, V2 (10,  V1(10,0)));
   Vs3 vs(10, Vs2 (10,  Vs1(10,"")));



   v[3][2][5]=3141;
   vs[3][2][5]="BANG!";

   Vs1 vs1;
   Vs2 vs2;
   Vs3 vs3;

   vs1.push_back("1 one");
   vs1.push_back("2 one");
   vs1.push_back("3 one");
   

   vs2.push_back(vs1);
   vs1.clear();

   vs1.push_back("1 two");
   vs1.push_back("2 two");
   vs1.push_back("3 two");


   vs2.push_back(vs1);

   // Example iterator
   //    V3::iterator it;

   cout << v[3][2][5] << endl;
   cout << vs[3][2][5] << endl;
   cout << vs2[1][1] << endl;
   
   vs2.resize(12);
   for(int i=0; i<12; ++i)
     {
       vs2[i].resize(12);
     }
 
   vs2[4][2]="This is 4 2 1";
   cout << vs2[4][2] << endl;


   // Dynamically working with 3D size

   int myNewSize=12;
   vs3.resize(myNewSize);
   for(int i=0; i<myNewSize; ++i)
     {
       vs3[i].resize(myNewSize);
       for(int j=0; j<myNewSize; ++j)
         vs3[i][j].resize(myNewSize);
     }

   vs3[3][2][5]="This is 3 2 5";
   cout << vs3[3][2][5] << endl;



}
