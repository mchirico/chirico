/* sicode.c - Sample of values for \codefn{si_code} on signal delivery */

#include <sys/signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifndef SI_TKILL
#define SI_TKILL -6
#endif

void handler(int signo, siginfo_t * info, void * f) {
    static int count = 0;

    printf("caught signal sent by ");
    switch (info->si_code) {
    case SI_USER:
	printf("kill()\n"); break;
    case SI_QUEUE:
	printf("sigqueue()\n"); break;
    case SI_TKILL:
	printf("tkill() or raise()\n"); break;
    case CLD_EXITED:
	printf("kernel telling us child exited\n"); exit(0);
    }

    if (++count == 4) exit(1);
}

int main() {
    struct sigaction act;
    union sigval val;
    pid_t pid = getpid();

    val.sival_int = 1234;

    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGCHLD, &act, NULL);

    kill(pid, SIGCHLD);
    sigqueue(pid, SIGCHLD, val);
    raise(SIGCHLD);

    /* To get a SIGCHLD from the kernel we create a child and
       have it exit immediately. The signal handler exits after
       receiving the signal from the kernel, so we just sleep for
       a while and let the program terminate that way. */

    if (!fork()) exit(0);
    sleep(60);

    return 0;
}
