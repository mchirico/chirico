#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>

#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  200


#define LISTENQ         1024

extern int h_errno;

ssize_t process(int sockfd)
{
  char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
  ssize_t n;

  snprintf(sendline, MAXSUB,
           "HELO squeezel.com\r\n");
  write(sockfd, sendline, strlen(sendline));
  n = read(sockfd, recvline, MAXLINE);
    recvline[n] = '\0';
    printf("%s", recvline);

  snprintf(sendline, MAXSUB,
           "MAIL FROM: xxx010@squeezel.com\r\n");
  write(sockfd, sendline, strlen(sendline));
  n = read(sockfd, recvline, MAXLINE);
    recvline[n] = '\0';
    printf("%s", recvline);


  snprintf(sendline, MAXSUB,
           "RCPT TO: xxx010@jefferson.edu\r\n");
  write(sockfd, sendline, strlen(sendline));

  n = read(sockfd, recvline, MAXLINE);
    recvline[n] = '\0';
    printf("%s", recvline);



  snprintf(sendline, MAXSUB,
           "DATA\r\n");
  write(sockfd, sendline, strlen(sendline));

  n = read(sockfd, recvline, MAXLINE);
    recvline[n] = '\0';
    printf("%s", recvline);


  snprintf(sendline, MAXSUB,
           "Subject: xxx010_test\r\nFrom:Mike.Chirico@gmail.com\r\n");
  write(sockfd, sendline, strlen(sendline));

  snprintf(sendline, MAXSUB,
           "This is test data for the server. Test 2.\n");
  write(sockfd, sendline, strlen(sendline));


  snprintf(sendline, MAXSUB,
           "\r\n.\r\n");
  write(sockfd, sendline, strlen(sendline));

  n = read(sockfd, recvline, MAXLINE);
    recvline[n] = '\0';
    printf("%s", recvline);




  return n;

}
int main(void)
{
  int sockfd;
  struct sockaddr_in servaddr;

  char **pptr;
  //********** You can change. Puy any values here *******
  char *hname = "smtp.jefferson.edu";

  //*******************************************************

  char str[50];
  struct hostent *hptr;
  if ((hptr = gethostbyname(hname)) == NULL) {
    fprintf(stderr, " gethostbyname error for host: %s: %s",
	    hname, hstrerror(h_errno));
    exit(1);
  }
  printf("hostname: %s\n", hptr->h_name);
  if (hptr->h_addrtype == AF_INET
      && (pptr = hptr->h_addr_list) != NULL) {
    printf("address: %s\n",
	   inet_ntop(hptr->h_addrtype, *pptr, str,
		     sizeof(str)));
  } else {
    fprintf(stderr, "Error call inet_ntop \n");
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(25);
  inet_pton(AF_INET, str, &servaddr.sin_addr);

  connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
  process(sockfd);
  close(sockfd);
  exit(0);

}
