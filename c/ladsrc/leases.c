/* leases.c - Uses leases to tell when other processes open files */

#define _GNU_SOURCE

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char ** fileNames;
int numFiles;

void handler(int sig, siginfo_t * siginfo, void * context) {
    /* When a lease is up, print a message and close the file. 
       We assume that the first file we open will get file 
       descriptor 3, the next 4, and so on. */

    write(1, "releasing ", 10);
    write(1, fileNames[siginfo->si_fd - 3], 
	  strlen(fileNames[siginfo->si_fd - 3]));
    write(1, "\n", 1);
    fcntl(siginfo->si_fd, F_SETLEASE, F_UNLCK);
    close(siginfo->si_fd);
    numFiles--;
}

int main(int argc, const char ** argv) {
    int fd;
    const char ** file;
    struct sigaction act;

    if (argc < 2) {
	fprintf(stderr, "usage: %s <filename>+\n", argv[0]);
	return 1;
    }

    /* Register the signal handler. Specifying SA_SIGINFO lets
       the handler learn which file descriptor had the lease
       expire. */
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaction(SIGRTMIN, &act, NULL);

    /* Store the list of filenames in a global variable so that
       the signal handler can access it. */
    fileNames = argv + 1;
    numFiles = argc - 1;

    /* Open the files, set the signal to use, and create the 
       lease */
    for (file = fileNames; *file; file++) {
	if ((fd = open(*file, O_RDONLY)) < 0) {
	    perror("open");
	    return 1;
	}

	/* We have to use F_SETSIG for the siginfo structure to
	   get filled in properly */
	if (fcntl(fd, F_SETSIG, SIGRTMIN) < 0) {
	    perror("F_SETSIG");
	    return 1;
	}

	if (fcntl(fd, F_SETLEASE, F_WRLCK) < 0) {
	    perror("F_SETLEASE");
	    return 1;
	}
    }

    /* As long as files remain open, wait for signals. */
    while (numFiles)
	pause();

    return 0;
}
