/* Copyright (c) GPL mchirico@users.sourceforge.net

   When arrays are passed as parameters to functions
   they "decay" to a pointer of the first element in
   the array; therefore, there is no way to get the
   size of the array from "sizeof(array)/sizeof(array[0])"
   within the function, because sizeof(array) is invalid.

   However, the techniques below will work.


*/
#include <iostream>
#include <string>
using namespace std;

template <typename T,int n, typename T2>
int give_size_init(T (&array)[n],T2 init_val)
{

  int i;
  for(i=0; i<n; i++)
    array[i]=init_val;
  return n;
}

int main(void)
{
  int a[13];
  string s[15];
  string s_init;


  cout << "Size of array is " << give_size_init(a,5) << endl;
  cout << "Size of array is " << give_size_init(s,"ta da") << endl;
  s_init="more";
  cout << "Size of array is " << give_size_init(s,s_init) << endl;
  return 0;
}
