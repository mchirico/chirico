/* dirchange.c - Tracks changes to directories as they occur */

#define _GNU_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* We use a linked list to store the names of all of the files in
   each directory. The exists field is used for housekeeping work
   when we check for changes. */
struct fileInfo {
    char * name;
    struct fileInfo * next;
    int exists;
};

/* This is a global array. It matches file descriptors to directory
   paths, stores a list of files in the directory, and gives a place
   for the signal handler to indicate that the directory needs to be
   rescanned. The last entry has a NULL path to mark the end of the
   array. */

struct directoryInfo {
    char * path;
    int fd;
    int changed;
    struct fileInfo * contents;
} * directoryList;

/* This will never return an empty list; all directories contain at
   least "." and ".." */
int buildDirectoryList(char * path, struct fileInfo ** listPtr) {
    DIR * dir;
    struct dirent * ent;
    struct fileInfo * list = NULL;

    if (!(dir = opendir(path))) {
	perror("opendir");
	return 1;
    }

    while ((ent = readdir(dir))) {
	if (!list) {
	    list = malloc(sizeof(*list));
	    list->next = NULL;
	    *listPtr = list;
	} else {
	    list->next = malloc(sizeof(*list));
	    list = list->next;
	}
	
	list->name = strdup(ent->d_name);
    }

    if (errno) {
	perror("readdir");
	closedir(dir);
	return 1;
    }

    closedir(dir);

    return 0;
}

/* Scans the directory path looking for changes from the previous
   contents, as specified by the *listPtr. The linked list is 
   updated to reflect the new contents, and messages are printed 
   specifying what changes have occured. */
int updateDirectoryList(char * path, struct fileInfo ** listPtr) {
    DIR * dir;
    struct dirent * ent;
    struct fileInfo * list = *listPtr;
    struct fileInfo * file, * prev;

    if (!(dir = opendir(path))) {
	perror("opendir");
	return 1;
    }

    for (file = list; file; file = file->next)
	file->exists = 0;

    while ((ent = readdir(dir))) {
	file = list;
	while (file && strcmp(file->name, ent->d_name))
	    file = file->next;

	if (!file) {
	    /* new file, add it to the list */
	    printf("%s created in %s\n", ent->d_name, path);
	    file = malloc(sizeof(*file));
	    file->name = strdup(ent->d_name);
	    file->next = list;
	    file->exists = 1;
	    list = file;
	} else {
	    file->exists = 1;
	}
    }

    closedir(dir);

    file = list;
    prev = NULL;
    while (file) {
	if (!file->exists) {
	    printf("%s removed from %s\n", file->name, path);
	    free(file->name);

	    if (!prev) {
		/* removing the head node */
		list = file->next;
		free(file);
		file = list;
	    } else {
		prev->next = file->next;
		free(file);
		file = prev->next;
	    }
	} else {
	    prev = file;
	    file = file->next;
	}
    }

    *listPtr = list;

    return 0;
}

void handler(int sig, siginfo_t * siginfo, void * context) {
    int i;

    for (i = 0; directoryList[i].path; i++) {
	if (directoryList[i].fd == siginfo->si_fd) {
	    directoryList[i].changed = 1;
	    return;
	}
    }
}

int main(int argc, char ** argv) {
    struct sigaction act;
    sigset_t mask, sigio;
    int i;

    /* Block SIGRTMIN. We don't want to receive this anywhere but 
       inside of the sigsuspend() system call. */
    sigemptyset(&sigio);
    sigaddset(&sigio, SIGRTMIN);
    sigprocmask(SIG_BLOCK, &sigio, &mask);

    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaction(SIGRTMIN, &act, NULL);

    if (!argv[1]) {
	/* no arguments given, fix up argc/argv to look like "." was
	   given as the only argument */
	argv[1] = ".";
	argc++;
    }

    /* each argument is a directory to watch */
    directoryList = malloc(sizeof(*directoryList) * argc);
    directoryList[argc - 1].path = NULL;

    for (i = 0; i < (argc - 1); i++) {
	directoryList[i].path = argv[i + 1];
	if ((directoryList[i].fd = 
		open(directoryList[i].path, O_RDONLY)) < 0) {
	    fprintf(stderr, "failed to open %s: %s\n", 
	            directoryList[i].path, strerror(errno));
	    return 1;
	}

	/* monitor the directory before scanning it the first time, 
	   ensuring we catch files created by someone else while 
	   we're scanning it. If someone does happen to change it, 
	   a signal will be generated (and blocked until we're 
	   ready for it) */
	if (fcntl(directoryList[i].fd, F_NOTIFY, DN_DELETE | 
		       DN_CREATE | DN_RENAME | DN_MULTISHOT)) {
	    perror("fcntl F_NOTIFY");
	    return 1;
	}

	fcntl(directoryList[i].fd, F_SETSIG, SIGRTMIN);

	if (buildDirectoryList(directoryList[i].path, 
			       &directoryList[i].contents))
	    return 1;
    }

    while (1) {
	sigsuspend(&mask);		    

	for (i = 0; directoryList[i].path; i++)
	    if (directoryList[i].changed)
		if (updateDirectoryList(directoryList[i].path, 
				   &directoryList[i].contents))
		    return 1;
    }

    return 0;
}
