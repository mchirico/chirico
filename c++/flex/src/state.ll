

%{

#include <math.h>
#include <string.h>

int num_lines = 0, num_chars = 0;
int state_chg[3];
int i;




%}
%option c++
%option noyywrap
%s  state0 state1 state2 

%%

\n           ++num_lines;  ++num_chars;

"a"           BEGIN(state0);
"b"           BEGIN(state1);
"c"           BEGIN(state2);
"t"           {
               int i;
               for(i=0; i< 3; ++i)
                   printf("state_chg[%d]=%d\n",i,state_chg[i]);

               }

"r"           {
               int i;
               for(i=0; i< 3; ++i)
                   {
                   state_chg[i]=0;
                   printf("state_chg[%d]=%d\n",i,state_chg[i]);
                   }

               }


<state0>"0"            {
                         printf("1");
                         ++state_chg[0];
                       }

<state0>"1"            {
                         printf("0");
                         ++state_chg[0];
                       }


<state1>"0"            {
                         printf("0");
                         ++state_chg[1];
                       }

<state1>"1"            {
                         printf("1");
                         ++state_chg[1];
                       }


<state2>"0"            {
                         printf("x");
                         ++state_chg[2];
                       }

<state2>"1"            {
                         printf("y");
                         ++state_chg[2];
                       }

<state2>"0110"            {
                           printf("ChangeState back to zero -->%s<--",yytext);
                           ++state_chg[2];
                           BEGIN(0);
                       }





.            ++num_chars;

%%
