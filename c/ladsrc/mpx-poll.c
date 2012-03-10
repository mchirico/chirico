/* mpx-poll.c - Displays input from two pipes using \codefn{poll()} */

#include <fcntl.h>
#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>

int main(void) {
    struct pollfd fds[2];
    char buf[4096];
    int i, rc;

    /* open both pipes */
    if ((fds[0].fd = open("p1", O_RDONLY | O_NONBLOCK)) < 0) {
        perror("open p1");
        return 1;
    }

    if ((fds[1].fd = open("p2", O_RDONLY | O_NONBLOCK)) < 0) {
        perror("open p2");
        return 1;
    }

    /* start off reading from both file descriptors */
    fds[0].events = POLLIN;
    fds[1].events = POLLIN;
 
    /* while we're watching one of fds[0] or fds[1] */
    while (fds[0].events || fds[1].events) {
        if (poll(fds, 2, 0) < 0) {
            perror("poll");
            return 1;
        } 

        /* check to see which file descriptors are ready to be
           read from */
        for (i = 0; i < 2; i++) {
            if (fds[i].revents) {
                /* fds[i] is ready for reading, go ahead... */
                rc = read(fds[i].fd, buf, sizeof(buf) - 1);
                if (rc < 0) {
                    perror("read");
                    return 1;
                } else if (!rc) {
                    /* this pipe has been closed, don't try
                       to read from it again */
                    fds[i].events = 0;
                } else {
                    buf[rc] = '\0';
                    printf("read: %s", buf);
                }
            }
        } 
    }

    return 0;
}
