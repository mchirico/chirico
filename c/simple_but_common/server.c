/* Copyright (c) GPL 2005, Mike Chirico mchirico@users.sourceforge.net

   The program is a TCP server on port 10000 that puts entries into 
   the log only. It can be setup as a daemon; but, current does not
   implement that daemon call.

   Note, this program runs as a daemon. You can check input as follows

     $ telnet localhost 10000
         <type some text>

   You will see an echo on the screen and results will be sent to the
   message log.

   To kill the program, you will have to find it with "ps auxf", then,
   do a "kill -9 on the <PSID>". Or find the PSID in the log files.

*/


#include <stdlib.h>
#include <syslog.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>


#define SA      struct sockaddr  /* keeps the lines shorter. Note sockaddr and not sockaddr_in; it's generic */
#define MAXLINE 4096
/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define LISTENQ         1024    /* 2nd argument to listen() */
#define MAXSOCKADDR  128        /* max socket address structure size */

/* normally these would go in a header */
void sig_chld(int);
void process_stuff(int);
int sockfd_to_family(int );

/*
  The follwing function prevents zombie or defunct processes:
  which occurs with server2way when the client is killed:


$ps -U chirico -auf    
chirico  30923  0.0  0.0  1352  252 pts/0    S    11:02   0:00  \_ ./server2way
chirico  30924  0.0  0.0     0    0 pts/0    Z    11:02   0:00      \_ [server2way <defunct>]  

  So, the function below...prevents the problem.

*/

void
sig_chld(int signo)
{
  pid_t pid;
  int stat;
  char wbuf[MAXLINE+1];
     
  while( (pid = waitpid ( -1, &stat, WNOHANG)) > 0 )
    {
     snprintf(wbuf,MAXLINE,"child %d terminated signo %d\n",pid,signo);  
     syslog(3,wbuf);	
    }
  return;

}


void 
process_stuff(int sockfd)
{
  ssize_t n;
  char line[MAXLINE];
  char wbuf[MAXLINE+1];

 
  
  sockfd_to_family(sockfd);
  while(1) {
    if ( ( n = read( sockfd, line, MAXLINE)) == 0 )
      {
	snprintf(wbuf,MAXLINE,"return in process_stuff ... read == 0\n");
	syslog(3,wbuf);
	return;

      }
    line[n]='\0';  
    snprintf(wbuf,MAXLINE,"client:n=%d %s\n",n,line);
    syslog(3,wbuf);
    write(sockfd, line, n);
  }
}


int 
sockfd_to_family(int sockfd)
{

  struct sockaddr_in sa;
  socklen_t len;
  char wbuf[MAXLINE+1];
  
  len = sizeof(sa);
  if (getpeername(sockfd, (struct sockaddr*) &sa, &len) < 0 )
    return -1;

  snprintf(wbuf,MAXLINE,"client: %s: %d\n",inet_ntoa(sa.sin_addr),(int) ntohs(sa.sin_port));
  syslog(3,wbuf);

  return(sa.sin_port);
}



/*

These are the major 4 steps:
  socket
  bind
  listen
    -- signal handle (optional but good if client it killed)
  accept
    -- accept does not return until there is a connection


*/


int 
main(void)
{
  int listenfd, connfd;
  pid_t childpid;
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr;
  
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port =  htons(10000);

  bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
  listen(listenfd, LISTENQ);

  signal(SIGCHLD, sig_chld);
  /* if everyhing is ok make a daemon */
  daemon(0,0);

  while(1)
    {
      clilen = sizeof(cliaddr);
      connfd = accept(listenfd, (SA *) &cliaddr, &clilen);
      
      if ( (childpid = fork()) == 0 ) {
	close(listenfd);
	process_stuff(connfd);
	exit(0);
      }
      close(connfd);
    }

}

