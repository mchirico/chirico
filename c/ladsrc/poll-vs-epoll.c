/* poll-vs-epoll.c - Compares the performance of \codefn{poll()} and \codefn{epoll} */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/signal.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>

#include <sys/select.h>

int gotAlarm;

void catch(int sig) {
     gotAlarm = 1;
}

#define OFFSET 10

int main(int argc, const char ** argv) {
    int pipeFds[2];
    int count;
    int numFds;
    struct pollfd * pollFds;
    struct epoll_event event;
    int epfd;
    int i;
    struct rlimit lim;
    char * end;

    if (!argv[1]) {
	fprintf(stderr, "number expected\n");
	return 1;
    }

    numFds = strtol(argv[1], &end, 0);
    if (*end) {
	fprintf(stderr, "number expected\n");
	return 1;
    }

    printf("Running test on %d file descriptors.\n", numFds);

    lim.rlim_cur = numFds + OFFSET;
    lim.rlim_max = numFds + OFFSET;
    if (setrlimit(RLIMIT_NOFILE, &lim)) {
	perror("setrlimit");
	exit(1);
    }

    pipe(pipeFds);

    pollFds = malloc(sizeof(*pollFds) * numFds);

    epfd = epoll_create(numFds);
    event.events = EPOLLIN;

    for (i = OFFSET; i < OFFSET + numFds; i++) {
	if (dup2(pipeFds[0], i) != i) {
	    printf("failed at %d: %s\n", i, strerror(errno));
	    exit(1);
	}

	pollFds[i - OFFSET].fd = i;
	pollFds[i - OFFSET].events = POLLIN;

	event.data.fd = i;
	epoll_ctl(epfd, EPOLL_CTL_ADD, i, &event);
    }

    /* use a signal to know when time's up */
    signal(SIGALRM, catch);

    count = 0;
    gotAlarm = 0;
    alarm(1);
    while (!gotAlarm) {
        poll(pollFds, numFds, 0);
        count++;
    }

    printf("poll() calls per second: %d\n", count);

    alarm(1);

    count = 0;
    gotAlarm = 0;
    alarm(1);
    while (!gotAlarm) {
        epoll_wait(epfd, &event, 1, 0);
        count++;
    }

    printf("epoll() calls per second: %d\n", count);

    return 0;
}
