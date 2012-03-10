/* sigval.c - Shows using \codefn{sigqueue()} to send data with a signal */

#include <sys/signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Catch a signal and record that it was handled. */
void handler(int signo, siginfo_t * si, void * context) {
    printf("%d\n", si->si_value.sival_int);
}

int main() {
    sigset_t mask;
    sigset_t oldMask;
    struct sigaction act;
    int me = getpid();
    union sigval val;

    /* Send signals to handler() and keep all signals blocked
       that handler() has been configured to catch to avoid
       races in manipulating the global variables. */
    act.sa_sigaction = handler;
    act.sa_mask = mask;
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGRTMIN, &act, NULL);

    /* Block SIGRTMIN so we can see the queueing and ordering */
    sigemptyset(&mask);
    sigaddset(&mask, SIGRTMIN);

    sigprocmask(SIG_BLOCK, &mask, &oldMask);

    /* Generate signals */
    val.sival_int = 1;
    sigqueue(me, SIGRTMIN, val);
    val.sival_int++;
    sigqueue(me, SIGRTMIN, val);
    val.sival_int++;
    sigqueue(me, SIGRTMIN, val);

    /* Enable delivery of the signals. */
    sigprocmask(SIG_SETMASK, &oldMask, NULL);

    return 0;
}
