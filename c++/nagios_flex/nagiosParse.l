%{

#include <math.h>
#include <string.h>
#include <time.h>


#define BufSizF 256
#define MaxBufSizF 2048

struct tm tm;
int num_lines = 0, num_chars = 0;
int state_chg[3];
int i;
int fp0,fp1,fp2,fp3,fp4,fp5;

char pbuf[MaxBufSizF];
char buf[BufSizF];
char tbuf[BufSizF];
char sbuf[BufSizF];
char cbuf[BufSizF];
char c2buf[BufSizF];
char *p;

%}


%s  state0 state1 state2 state3 state4 state5 state6 state7 state8 skip
%s  state9 state10 state11

%s  lstate0 lstate1 lstate2 

%s  mstate0 mstate1 mstate2 

%s   pstate0 pstate1 pstate2

%s   dpstate0 dpstate1 dpstate2

DIGIT    [0-9]
CAP      [A-Z]


%%

\n             ++num_lines;  ++num_chars; BEGIN(state0);



^"["              BEGIN(state1);

<state1>{DIGIT}*  {
                  snprintf(buf,BufSizF,"%s",yytext);
                  BEGIN(state2);
                  }

<state2>"] "      { 
                   BEGIN(state3);
                  }


<state3>"LOG".*  {
         /*     To find all skip states, use the following:        

                 cut -d ';' -f3 data|cut -d ':' -f1|sort|uniq > mout   

         */
                  BEGIN(skip);
                 }

<state3>"Auto-save".* {
                  BEGIN(skip);
                 }

<state3>"Successfully".* {
                  BEGIN(skip);
                 }

<state3>"Bailing".* {
                  BEGIN(skip);
                 }

<state3>"Finished daemonizing".* {
                  BEGIN(skip);
                 }

<state3>"Error".* {
                  BEGIN(skip);
                 }


<state3>"Caught".* {
                  BEGIN(skip);
                 }

<state3>"Lockfile".* {
                  BEGIN(skip);
                 }

<state3>"Nagios".* {
                  BEGIN(skip);
                 }

<state3>"Warning".* {
                  BEGIN(skip);
                 }

<state3>"EXTERNAL COMMAND:" {
                  //snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(skip);
                 }





<state3>"CURRENT HOST STATE:" {
                  snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(state4);
                 }

<state3>"CURRENT SERVICE STATE:" {
                  snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(state4);
                 }


<state3>"HOST ALERT:" {
                  snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(state4);
                 }

<state3>"HOST DOWNTIME ALERT:" {
                  snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(state4);
                 }

<state3>"HOST NOTIFICATION:" {
                  snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(state4);
                 }

<state3>"SERVICE ALERT:" {
                  snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(state4);
                 }

<state3>"SERVICE DOWNTIME ALERT:" {
                  snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(state4);
                 }

<state3>"SERVICE NOTIFICATION:" {
                  snprintf(sbuf,BufSizF,"%s",yytext);
                  BEGIN(state4);
                 }

<state4>" " {
                  BEGIN(state5);
            }
 

<state5>[A-Z|a-z|0-9][A-Z|a-z|0-9|\.|\-]* {
                 //fprintf(stderr,"%s\n",yytext);
                  snprintf(cbuf,BufSizF,"%s",yytext);
                  BEGIN(state6);
              }

<state6>";"  {
                  BEGIN(state7);
             }

<state7>[A-Z|a-z|0-9][A-Z|a-z|0-9|\.|\-]* {
                  snprintf(c2buf,BufSizF,"%s",yytext);
                  BEGIN(state8);
              }


<state8>" Jobs".*   {
                  BEGIN(skip);
                 // printf("%s\n",yytext);
             }

<state8>" Listener".*   {
                  BEGIN(skip);
                 // printf("%s\n",yytext);
             }

<state8>.*"CHECK_NRPE: Error - Could not complete SSL handshake." {
                 BEGIN(skip);
            }

<state8>" Load"   {
                  BEGIN(lstate0);
               //   printf("%s\n",yytext);
             }

<state8>"Memory;" {
                  BEGIN(mstate0);
              }

<state8>"Total Processes;" {
                  BEGIN(pstate0);
              }

<state8>"Disk Partitions;" {
                  BEGIN(dpstate0);
              }
<dpstate0>.*" - free space:" {
                  BEGIN(dpstate1);
              }
<dpstate1>.*  {
                  BEGIN(skip);
    		  strptime((const char *)buf, "%s",&tm);
  		  strftime(tbuf, sizeof(tbuf), "%Y%U; %Y-%m-%d %H:%M:%S", &tm);

                  p=yytext;
                 snprintf(pbuf,MaxBufSizF,"%s; %s; %s; %s\n",tbuf,cbuf,c2buf,p);
                 write(fp3,pbuf,strlen(pbuf));

              }


<pstate0>.*  {
                  BEGIN(skip);
    		  strptime((const char *)buf, "%s",&tm);
  		  strftime(tbuf, sizeof(tbuf), "%Y%U; %Y-%m-%d %H:%M:%S", &tm);

                  p=yytext;
                  while(*p++ != '\0') {
                    if (*p == ':') {p++; break; }
                  }
                 snprintf(pbuf,MaxBufSizF,"%s; %s; %s; %s\n",tbuf,cbuf,c2buf,p);
                 write(fp2,pbuf,strlen(pbuf));
       
             }

<mstate0>"Mem: "  {
                  BEGIN(mstate1);
              }

<mstate1>.*   {
                BEGIN(skip);
                p=yytext;


    		  strptime((const char *)buf, "%s",&tm);
  		  strftime(tbuf, sizeof(tbuf), "%Y%U; %Y-%m-%d %H:%M:%S", &tm);

                snprintf(pbuf,MaxBufSizF,"%s; %s; %s; %s\n",tbuf,cbuf,c2buf,p);
                write(fp1,pbuf,strlen(pbuf));
              }


<lstate0>.*"- load average:" {
                  BEGIN(lstate1);
                //printf("%s\n",yytext);

             }

<lstate1>.*  {
                BEGIN(skip);
    		  strptime((const char *)buf, "%s",&tm);
  		  strftime(tbuf, sizeof(tbuf), "%Y%U; %Y-%m-%d %H:%M:%S", &tm);

                p=yytext;
                while(*p) {
                 if(*p == ',') { *p=';'; }
                 p++;
                }
                snprintf(pbuf,MaxBufSizF,"%s; %s; %s; %s\n",tbuf,cbuf,c2buf,yytext);
                write(fp0,pbuf,strlen(pbuf));
                  //printf("[%s]; %s; %s; {%s} {%s} %s\n",buf,tbuf,sbuf,cbuf,yytext); 
              } 





<state9>.*    {
                  BEGIN(skip);
    		  strptime((const char *)buf, "%s",&tm);
  		  strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", &tm);
                  //printf("[%s]; %s; %s; {%s} {%s} %s\n",buf,tbuf,sbuf,cbuf,c2buf,yytext); 
                  //printf("%s %s\n",cbuf,c2buf); 
                  printf("%s\n",yytext); 


                  }



.            ++num_chars;

%%
