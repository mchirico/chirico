/* select-vs-poll.c - Compares the performance of \codefn{select()} and \codefn{poll()} */

#include <fcntl.h>
#include <stdio.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <unistd.h>

int gotAlarm;

void catch(int sig) {
     gotAlarm = 1;
}

#define HIGH_FD 1000

int main(int argc, const char ** argv) {
    int devZero;
    int count;
    fd_set selectFds;
    struct pollfd pollFds;

    devZero = open("/dev/zero", O_RDONLY);
    dup2(devZero, HIGH_FD);

    /* use a signal to know when time's up */
    signal(SIGALRM, catch);

    gotAlarm = 0;
    count = 0;
    alarm(1);
    while (!gotAlarm) {
        FD_ZERO(&selectFds);
        FD_SET(HIGH_FD, &selectFds);

        select(HIGH_FD + 1, &selectFds, NULL, NULL, NULL);
        count++;
    }

    printf("select() calls per second: %d\n", count);

    pollFds.fd = HIGH_FD;
    pollFds.events = POLLIN;
    count = 0;
    gotAlarm = 0;
    alarm(1);
    while (!gotAlarm) {
        poll(&pollFds, 0, 0);
        count++;
    }

    printf("poll() calls per second: %d\n", count);

    return 0;
}
