/* itimer.c - Demonstrates use of interval timers */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>


void catch_signal (int ignored) {
    static int iteration=0;

    printf("caught interval timer signal, iteration %d\n", 
	   iteration++);
}

pid_t start_timer (int interval) {
    pid_t child;
    struct itimerval it;
    struct sigaction sa;

    if (!(child = fork())) {
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = catch_signal;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;

        sigaction(SIGALRM, &sa, NULL);

        memset(&it, 0, sizeof(it));
        it.it_interval.tv_sec = interval;
        it.it_value.tv_sec = interval;
        setitimer(ITIMER_REAL, &it, NULL);

        while (1) pause();
    }

    return child;
}

void stop_timer (pid_t child) {
    kill (child, SIGTERM);
}

int main (int argc, const char **argv) {
    pid_t timer = 0;

    printf("Demonstrating itimers for 10 seconds, "
	   "please wait...\n");
    timer = start_timer(1);
    sleep(10);
    stop_timer(timer);
    printf("Done.\n");

    return 0;
}
