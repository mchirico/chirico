/* queued.c - Demonstration of signal queuing and reordering */

/* get the definition of strsignal() from string.h */
#define _GNU_SOURCE 1

#include <sys/signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Globals for building a list of caught signals */
int nextSig = 0;
int sigOrder[10];

/* Catch a signal and record that it was handled. */
void handler(int signo) {
    sigOrder[nextSig++] = signo;
}

int main() {
    sigset_t mask;
    sigset_t oldMask;
    struct sigaction act;
    int i;

    /* Signals we're handling in this program */
    sigemptyset(&mask);
    sigaddset(&mask, SIGRTMIN);
    sigaddset(&mask, SIGRTMIN + 1);
    sigaddset(&mask, SIGUSR1);

    /* Send signals to handler() and keep all signals blocked
       that handler() has been configured to catch to avoid
       races in manipulating the global variables. */
    act.sa_handler = handler;
    act.sa_mask = mask;
    act.sa_flags = 0;

    sigaction(SIGRTMIN, &act, NULL);
    sigaction(SIGRTMIN + 1, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);

    /* Block the signals we're working with so we can see the
       queuing and ordering behavior. */
    sigprocmask(SIG_BLOCK, &mask, &oldMask);

    /* Generate signals */
    raise(SIGRTMIN + 1);
    raise(SIGRTMIN);
    raise(SIGRTMIN);
    raise(SIGRTMIN + 1);
    raise(SIGRTMIN);
    raise(SIGUSR1);
    raise(SIGUSR1);

    /* Enable delivery of the signals. They'll all be delivered
       right before this call returns (on Linux; this is NOT
       portable behavior). */
    sigprocmask(SIG_SETMASK, &oldMask, NULL);

    /* Display the ordered list of signals we caught */
    printf("signals received:\n");
    for (i = 0; i < nextSig; i++) 
        if (sigOrder[i] < SIGRTMIN)
            printf("\t%s\n", strsignal(sigOrder[i]));
        else
            printf("\tSIGRTMIN + %d\n", sigOrder[i] - SIGRTMIN);

    return 0;
}
