/*
 There are a few errors in this program, like the assumption that
 child thread pid will be 1 less than parent. Hmm, maybe on a system
 that isn't busy.

 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>
pid_t self_pid;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void fork_prepare(void)
{
  int status;
  status = pthread_mutex_lock(&mutex);
  if (status != 0)
    fprintf(stderr,"Lock in handler");
}
void fork_parent(void)
{
  int status;
  status = pthread_mutex_unlock(&mutex);
  if (status != 0)
    fprintf(stderr,"unlock in parent handler");
}

void fork_child (void)
{
  int status;
  self_pid = getpid();
  status = pthread_mutex_unlock(&mutex);
  if (status != 0)
    fprintf(stderr,"unlock child handler");
}

void *thread_routine (void *arg)
{
  pid_t child_pid;
  int status;

  child_pid = fork();
    fprintf(stderr,"child not equal to pid_t -1: child %d parent %d\n",child_pid,self_pid);

  status = pthread_mutex_lock(&mutex);
  if (status != 0)
    fprintf(stderr,"Lock in child\n");
  status = pthread_mutex_unlock (&mutex);
  if (status != 0)
    fprintf(stderr,"Unlock in child\n");
  if (child_pid !=0 ) {
    if ((pid_t)-1 == waitpid (child_pid, (int*)0, 0))
      fprintf(stderr,"Wait for child");
  }
  return NULL;
}

int main(int argc, char **argv)
{
  pthread_t fork_thread;
  int atfork_flag = 1;
  int status;
  if (argc > 1)
    atfork_flag = atoi(argv[1]);
  if (atfork_flag) {
    status = pthread_atfork (
			    fork_prepare, fork_parent, fork_child);
    if (status != 0)
      fprintf(stderr,"Register fork handlers");
  }
  self_pid = getpid();
  status = pthread_mutex_lock(&mutex);
  if (status != 0)
    fprintf(stderr,"Lock mutex\n");
  status = pthread_create (
			   &fork_thread, NULL, thread_routine, NULL);
  if (status != 0)
    fprintf(stderr,"status zero\n");
  sleep(4);
  status = pthread_mutex_unlock(&mutex);
  if (status != 0)
    fprintf(stderr,"Unlock mutex\n");
  status = pthread_join(fork_thread, NULL);
  if (status != 0)
    fprintf(stderr,"Join thread\n");
  return 0;
}



