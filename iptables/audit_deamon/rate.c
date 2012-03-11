#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


int rate(int dsec, int dusec)
{
	char buffer[30];
	struct timeval tv;
	time_t curtime;
	gettimeofday(&tv, NULL);

	double ct = 0;
	double dt = 0;
	static double st = 0.0;

	ct = (double) tv.tv_sec + (double) tv.tv_usec / 1000000;
	dt = (double) dsec + (double) dusec / 1000000;



	if (st == 0.0) {
		st = ct;
		return 1;
	} else {
		if ((st + dt) <= ct) {
			st = ct;
			printf("%f\n", st);
			return 1;
		}
	}

	return 0;

}



int main(void)
{

	int i;

	for (i = 0; i < 100000; ++i)
		if (rate(0, 53400) == 1)
			printf(" **************** \n");
	sleep(4);
	if (rate(0, 53400) == 1)
		printf(" **************** \n");

	return 0;



}
