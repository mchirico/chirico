/*
    gcc prtids.c -o prtids -lpthread

*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THRD 20

typedef struct str_thread
{
  int thread_no;
  char data[50];
  long i;
  double d;
} tdata;

tdata td[NUM_THRD];


pthread_t ntid[NUM_THRD];

void
printids (const char *s, void *arg)
{
  pid_t pid;
  pthread_t tid;
  tdata *d;
  long i,j,k;

  d = (tdata *) arg;

  pid = getpid ();
  tid = pthread_self ();

  if (d->thread_no == 0 ) {
    printf("Thread zero\n");
    for(i=0; i < 300; ++i ){
      sleep(1);
      for(j=0; j < NUM_THRD; ++j){
	printf("td[%i]=%ld\n",j,td[j].i);
      }
    }
  } else {

  
  k=0;
  for(i=0; i < 3000; ++i)
    for(j=0; j < 30000; ++j)
      {
      k+=j+i;
      td[ d->thread_no ].i = k;
      }
  }

  printf ("%s pid %u tid %u (0x%x) data:%s (k=%ld)\n", s, (unsigned int) pid,
	  (unsigned int) tid, (unsigned int) tid, d->data,k);
}

void *
thr_fn (void *arg)
{

  printids ("new thread: ", arg);
  return ((void *) 0);
}

int
main (void)
{
  int err;
  int i;


  for (i = 0; i < NUM_THRD; ++i)
    {
      td[i].thread_no=i;
      td[i].i=0;
      snprintf (td[i].data, 50, "Thread %d", i);
    }



  for (i = 0; i < NUM_THRD; ++i)
    {
      err = pthread_create (&ntid[i], NULL, thr_fn, (void *) &td[i]);
      if (err != 0)
	fprintf (stderr, "can't create thread: %s\n", strerror (err));
    }
  for (i = 0; i < NUM_THRD; ++i)
    {
      pthread_join (ntid[i], NULL);
    }


  exit (0);
}
