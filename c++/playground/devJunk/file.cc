#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
using std::fixed;
using std::ios;
using std::left;
using std::right;
using std::showpoint;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <cstdlib>
using std::string;

#include <iomanip>
using std::setw;
using std::setprecision;

int main(void)
{

  string file_in="data.dat";
  string file_out="dataout.dat";
  string s("");
   
  ifstream fin(file_in.c_str(), ios::in);
  ofstream fout(file_out.c_str(), ios::out);


  if (!fin) {
    cerr << "cannot open file: " << file_in << endl;
    exit(1);
  }
  while (getline(fin,s))
    {
      cout << s << endl;
      fout << s << endl;
      if (s.find("1") != -1)
	{
       cout << "FOUND " << s.find("1") << endl;

	}else {
       cout << "NOT Found !!" << s.find("1") << endl;
	
      }
    }

    


  fin.close();
  fout.close();


}
