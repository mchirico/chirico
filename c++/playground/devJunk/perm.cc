#include <iostream>
#include <algorithm>
using namespace std;

int main () {
  int myints[] = {1,2,3};
  int num=sizeof(myints)/sizeof(myints[0]);
    

    cout << "The " << num <<
    "! possible permutations with" <<
    num
    <<  " elements:\n";


    sort (myints,myints+num);

    do {
        for (int i =0; i < num; ++i)
            cout << " " << myints[i];
        cout << endl;
    } while ( next_permutation (myints,myints+num ));


    return 0;
}
