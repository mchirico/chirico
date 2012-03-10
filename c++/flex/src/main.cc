/* Copyright GPL 2007 by Mike Chirico <mchirico@users.sourceforge.net>
    Updated: Mon May 28 10:39:07 EDT 2007


   Simple example of a flex++ (flex with c++) parser to generate
   transition states.

   The parser file state.l

   Example Usage:
   
             $ ./main
             a<return>
             0111<return>
             1000
             t
             state_chg[0]=4
             state_chg[1]=0
             state_chg[2]=0
             c
             0110
             ChangeState back to zero -->0110<--
             t
             state_chg[0]=4
             state_chg[1]=0
             state_chg[2]=1

      Above you type in an "a" and hit return. Then, type in 0111 and hit return.
      The program will respond with 1000. The command "t" is for telling the 
      transition state.


    Compile the program as follows:


      $ flex++ -ostate.cc state.ll
      $ g++ -o main main.cc state.cc -lfl



    You might want to download the complete source.
      http://sourceforge.net/project/showfiles.php?group_id=79320&package_id=233377

*/
#include <stdlib.h>
#include <stdio.h>
#include <FlexLexer.h>

extern int num_lines;
extern int num_chars;
extern int state_chg[];
extern int i;



int main(void)
{
        int i;
	FlexLexer* lexer = new yyFlexLexer;

        for(i=0; i<3; ++i) {
          state_chg[i]=0;
         }


	lexer->yylex();
        printf("\nFinal Status:\n"
               "  state_chg[0]=%d\n"
               "  state_chg[1]=%d\n"
               "  state_chg[2]=%d\n",
                  state_chg[0],state_chg[1],state_chg[2]);


	delete lexer;
        return 0;
}
