#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main(void)
{


    vector<string> v;
    stringstream ss;

    for (int i=1; i<20; ++i)
    {
        ss << "primes" << i << ".txt";
        v.push_back(ss.str());
        ss.str("");
    }
    for (vector<string>::iterator itr = v.begin(); itr != v.end(); ++itr)
        cout << *itr << endl;

}
