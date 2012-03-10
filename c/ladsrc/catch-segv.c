/* catch-segv.c - Display fields from \codefn{siginfo_t} for \codefn{SIGSEGV} */

#include <sys/signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signo, siginfo_t * info, void * f) {
    printf("caught ");
    if (info->si_signo == SIGSEGV)
        printf("segv accessing %p", info->si_addr);
    if (info->si_code == SEGV_MAPERR)
        printf(" SEGV_MAPERR");
    printf("\n");

    exit(1);
}

int main() {
    struct sigaction act;

    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act, NULL);

    *((int *) NULL) = 1;

    return 0;
}
