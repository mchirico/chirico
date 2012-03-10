/* mpx-epoll.c - Displays input from two pipes using \codefn{epoll} */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <sys/poll.h>

void addEvent(int epfd, char * filename) {
    int fd;
    struct epoll_event event;

    if ((fd = open(filename, O_RDONLY | O_NONBLOCK)) < 0) {
        perror("open");
        exit(1);
    }

    event.events = EPOLLIN;
    event.data.fd = fd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event)) {
	perror("epoll_ctl(ADD)");
	exit(1);
    }
}

int main(void) {
    char buf[4096];
    int i, rc;
    int epfd;
    struct epoll_event events[2];
    int num;
    int numFds;

    epfd = epoll_create(2);
    if (epfd < 0) {
	perror("epoll_create");
	return 1;
    }

    /* open both pipes and add them to the epoll set */
    addEvent(epfd, "p1");
    addEvent(epfd, "p2");

    /* continue while we have one or more file descriptors to 
       watch */
    numFds = 2;
    while (numFds) {
	if ((num = epoll_wait(epfd, events, 
	                     sizeof(events) / sizeof(*events), 
			     -1)) <= 0) {
            perror("epoll_wait");
            return 1;
        } 

        for (i = 0; i < num; i++) {
	    /* events[i].data.fd is ready for reading */

	    rc = read(events[i].data.fd, buf, sizeof(buf) - 1);
	    if (rc < 0) {
		perror("read");
		return 1;
	    } else if (!rc) {
		/* this pipe has been closed, don't try
		   to read from it again */
		if (epoll_ctl(epfd, EPOLL_CTL_DEL,
			      events[i].data.fd, &events[i])) {
		    perror("epoll_ctl(DEL)");
		    return 1;
		}

		close(events[i].data.fd);

		numFds--;
	    } else {
		buf[rc] = '\0';
		printf("read: %s", buf);
	    }
        } 
    }

    close(epfd);

    return 0;
}
