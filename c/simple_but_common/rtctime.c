/*
 *      Take from Paul Gortmaker's linux-<kernel version>/Documentation/rtc.txt 
 *      program in the kernel.
 *	Copyright (C) 1996, Paul Gortmaker.
 *
 *	Released under the GNU General Public License, version 2,
 *	included herein by reference.
 *
 *      Mike Chirico added call to localtime
 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(void) {

int i, fd, retval, irqcount = 0;
unsigned long  data;

char buf[80];
time_t ticks;

fd = open ("/dev/rtc", O_RDONLY);

if (fd ==  -1) {
	perror("/dev/rtc");
	exit(errno);
}

fprintf(stderr, "\n\t\t\tRTC Driver Test Example.\n\n");

/* Turn on update interrupts (one per second) */
retval = ioctl(fd, RTC_UIE_ON, 0);
if (retval == -1) {
	perror("ioctl");
	exit(errno);
}

fprintf(stderr, "Counting 5 update (1/sec) interrupts from reading /dev/rtc:\n");
fflush(stderr);
for (i=1; i<6; i++) {
	/* This read will block */
	retval = read(fd, &data, sizeof(unsigned long));
	if (retval == -1) {
		perror("read");
		exit(errno);
	}

        ticks = time(NULL);
	strftime(buf,30,"%H:%M:%S\n",localtime(&ticks));
	fprintf(stderr, " %s",buf);
	fflush(stderr);
	irqcount++;
}




close(fd);
return 0;

} /* end main */
