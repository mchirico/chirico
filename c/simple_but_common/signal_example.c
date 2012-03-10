/*

  This is a sample program demonstrating the use of signals

  $ gcc signal_example.c -o signal_example
  $ ./signal_example &
    [1] 31365
  $ kill -USR1 31365
    Yes..got SIGUSR1
  $ kill -USR2 31365
    Yes..got SIGUSR2




*/



#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_usr(int);

int main(void)
{

	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		fprintf(stderr, "can't catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		fprintf(stderr, "can't catch SIGUSR2");

	for (;;)
		pause();
	return 0;
}

static void sig_usr(int signo)
{
	if (signo == SIGUSR1)
		fprintf(stderr, "Yes..got SIGUSR1\n");
	else if (signo == SIGUSR2)
		fprintf(stderr, "Yes..got SIGUSR2\n");
	else
		fprintf(stderr, "Got some WACKY signal\n");
}
