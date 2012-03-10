/* Copyright (c) GPL 2005 Mike Chirico mchirico@users.sourceforge.net

  This is an example of using a duplex connection with ssh. You will
  need to fill in the computer you are trying to ssh to.

      $ ssh tape 'some command'

  See http://chirico.org/sshtips.htm  on how to work with ssh. Above
  "tape" is the name of the computer.

  Commands going into ssh come from pipedrv.c
  
    write(fileno(stdout),"uname -a\n",strlen("uname -a\n"));
    write(fileno(stdout),"date \n",strlen("date \n"));
    write(fileno(stdout),"exit\n",strlen("exit\n"));

  Note, output goes into the file "pipe_data".



*/



#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pty.h>

void Pipe(int *fds)
{
	if (pipe(fds) < 0)
		fprintf(stderr, "pipe error");
}

pid_t Fork(void)
{
	pid_t pid;

	if ((pid = fork()) == -1)
		fprintf(stderr, "fork error");
	return (pid);
}

void Close(int fd)
{
	if (close(fd) == -1)
		fprintf(stderr, "close error");
}


pid_t Waitpid(pid_t pid, int *iptr, int options)
{
	pid_t retpid;

	if ((retpid = waitpid(pid, iptr, options)) == -1)
		fprintf(stderr, "waitpid error");
	return (retpid);
}


int main(void)
{
	int pipe1[2], pipe2[2];
	pid_t childpid;
        int fd;

	Pipe(pipe1);
	Pipe(pipe2);

	if ((childpid = forkpty(&fd,0,0,0)) == 0) {
		Close(pipe1[1]);
		Close(pipe2[0]);

		if (dup2(pipe1[0], STDIN_FILENO) == -1)
			fprintf(stderr,
				"Failed: dup2 pipe1[0] STDIN_FILENO\n");

		if (dup2(pipe2[1], STDOUT_FILENO) == -1)
			fprintf(stderr,
				"Failed: dup2 pipe2[1] STDIN_FILENO\n");


                execlp("/usr/bin/ssh", "ssh", "tape", NULL);

                close(fd);

		exit(0);
	}

	Close(pipe1[0]);
	Close(pipe2[1]);

	if (dup2(pipe2[0], STDIN_FILENO) == -1)
		fprintf(stderr, "sFailed: dup2 pipe2[0] STDIN_FILENO\n");

	if (dup2(pipe1[1], STDOUT_FILENO) == -1)
		fprintf(stderr, "sFailed: dup2 pipe1[0] STDIN_FILENO\n");


          execlp("./pipedrv", "pipedrv", NULL);






	Waitpid(childpid, NULL, 0);
	close(fd);
	exit(0);
}
