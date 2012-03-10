/* This example of hanoi is based on Mark Jason Donminus'
   book "High Order Perl: Transforming Programs with Programs".

   http://hop.perl.plover.com/Examples/

   Obviously Mark does his programs in Perl, but doing them
   in C++, I think complements his work.


   This is an example of functional programming and recursion. But more
   interesting note the similarity of the Hanoi problem to gray codes.

      http://en.wikipedia.org/wiki/Gray_code
  
      http://en.wikipedia.org/wiki/Towers_of_Hanoi

*/


#include <iostream>
#include <cstdlib>
using namespace std;


void print_instructions(long n, const char* start, const char* end)
{
  cout << "Move disk #" << n << " from  " << start << " to " << end << endl;
}


/* The default function call is print_instrcutions
 */
void hanoi (long n, const char* start, const char* end, const char* extra, void (*fp)(long n,const char*, const char*) = print_instructions)
{
  if (n <= 1) {
    print_instructions(n,start,end);
  } else {
    hanoi(n-1,start, extra, end,fp);
    print_instructions(n,start,end);
    hanoi(n-1,extra,end,start,fp);
  }

}

int main(int argc, char** argv)
{

  char *offset;
  long n=3;
  if(argc == 2) {
     n=strtol(argv[1],&offset,0);
  }


  cout << "Calculating hanoi for " << n << " values" << endl;
  hanoi(n,"A","C","B",print_instructions);

  /* An acceptable call is the following, which by default calls print_instructions
  hanoi(n,"A","C","B",print_instructions);
  */

}
