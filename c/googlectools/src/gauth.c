/*  
# Copyright 2008 Mike Chirico mchirico@gmail.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>

#include "version.h"
#include "googlectools.h"
extern int errno;
#define MAXBUF  4096

static char email[MAXBUF];
static char passwd[MAXBUF];
static char service[MAXBUF];
static char file[MAXBUF];



int write_token(char *t, const char *rcfile)
{
	int fd;


	if ((fd = open(rcfile, O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "write_token error in file open: %s\n",
			strerror(errno));
		return 1;
	}
	write(fd, t, strlen(t));
	write(fd, "\n", 1);
	close(fd);
	return 0;


}



int mygetopt(int argc, char **argv)
{

	email[0] = '\0';
	passwd[0] = '\0';
	service[0] = '\0';
	char *p = 0;


	snprintf(service,MAXBUF,"ah");

	p = getenv("HOME");
	if (p != NULL)
		snprintf(file, MAXBUF, "%s/%s", p, ".gauthrc");
	else
		snprintf(file, MAXBUF, "%s", ".gauthrc");


	int c = 0;
	int flags = 0;

	while (1) {

		int option_index = 0;
		static struct option long_options[] = {
			{"help", 0, 0, 'h'},
			{"email", 1, 0, 'e'},
			{"password", 1, 0, 'p'},
			{"version", 0, 0, 'v'},
			{"service", 1, 0, 's'},
			{"file", 1, 0, 'f'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "he:p:vs:f:",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			printf("option %s",
			       long_options[option_index].name);
			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
			break;

		case 'h':
			flags |= 0x1;
			printf("gauth -e <email> -p <password> -s <site>\n"
			       "Example:  ./gauth -e billybob@gmail.com -p Pa33word -s www.cwxstat.org\n");
			exit(0);
			break;

		case 'e':
			flags |= 0x2;
			snprintf(email, MAXBUF, "%s", optarg);
			break;

		case 'p':
			flags |= 0x4;
			snprintf(passwd, MAXBUF, "%s", optarg);
			break;

		case 'v':
			flags |= 0x8;
			printf
			    ("Copyright (C) GPL 2008 by Mike Chirico <mchirico@gmail.com>\n"
			     "version %s \n" "  try --help\n" "Download:\n"
			     "  <need to fill in>\n" "Subversion:\n"
			     "  svn checkout http://chirico.googlecode.com/svn/trunk/c/GoogleAuthenticate gauth\n"
			     "Source:\n"
			     "  http://chirico.googlecode.com/svn/trunk/c/GoogleAuthenticate/src/gauth.c\n\n",
			     VERSION);

			exit(0);
			break;

		case 's':
			flags |= 0x10;
			snprintf(service, MAXBUF, "%s", optarg);
			break;

		case 'f':
			flags |= 0x40;
			snprintf(file, MAXBUF, "%s", optarg);
			break;


		case '?':
			break;

		default:
			printf
			    ("?? getopt returned character code 0%o ??\n",
			     c);
		}
	}

	if (optind < argc) {
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		printf("\n");
	}

	if (flags & 0x1) {
		printf("h flag\n");
	}
	if (~flags & 0x06) {
		fprintf(stderr,
			"This program generates a Google auth token\n"
			"from a gmail account name and password\n"
			"Usage:\n\tgauth -e <email> -p <password>  -s <service ah|cl|wise>\n"
			"Example:\n\tgauth -e mchirico@gmail.com -p Pa22word -s ah\n");
		exit(2);
	}

	return 1;
}






int main(int argc, char **argv)
{

	mygetopt(argc, argv);

	char *auth = gauth(email, passwd,service);
	if (auth != NULL) {
		printf("%s\n", auth);
		write_token(auth, file);
	} else
		return 1;


	return 0;

}
