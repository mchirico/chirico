/*  You could put your own name in for abcd to
    see if there are any valid word permutations

    Download:
    http://prdownloads.sourceforge.net/cpearls/simple_but_common_cpp.tar.gz?download

    You can find a large dictionary of words at the following link:
    http://prdownloads.sourceforge.net/souptonuts/linuxwords.1.tar.gz?download
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int main(void)
{
  char a[]="abcd";
  int r=1;
  size_t len = strlen(a);


  cout << a << "\t";
  while(next_permutation(a,a+len)){
    cout << a;
    (r++ % len+2 == len+1) ? cout <<  "\n": cout << "\t";
   }
}
