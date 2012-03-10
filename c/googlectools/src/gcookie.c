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
#define MAXR    1096

static char email[MAXBUF];
static char passwd[MAXBUF];
static char site[MAXBUF];
static char authfile[MAXBUF];
static char file[MAXBUF];	/* cookie */



char *read_auth(char *infile)
{
	static char buf[MAXBUF];
	static char s[MAXBUF];
	char *p = 0;
	int fd = 0;
	size_t j = MAXBUF;
	ssize_t n = 0;

	s[0] = '\0';


	if ((fd = open(infile, O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "write_token error in file open: %s\n",
			strerror(errno));
		return s;
	}
	while ((n = read(fd, buf, MAXR)) > 0) {
		buf[n] = '\0';
		strncat(s, buf, j);
		j = j - (size_t) n;
	}

	p = s;
	while (*p++) {
		if (*p == '\n') {
			*p = '\0';
		}
	}
	if (strstr(s, "Auth=") != NULL)
		return &s[5];
	else {
		s[0] = '\0';
		return s;
	}
}




int mygetopt(int argc, char **argv)
{

	email[0] = '\0';
	passwd[0] = '\0';
	site[0] = '\0';
	char *p = 0;

	p = getenv("HOME");
	if (p != NULL) {
		snprintf(authfile, MAXBUF, "%s/%s", p, ".gauthrc");
		snprintf(file, MAXBUF, "%s/%s", p, ".gcookierc");
	} else {
		snprintf(authfile, MAXBUF, "%s", ".gauthrc");
		snprintf(file, MAXBUF, "%s", ".gcookierc");
	}




	int c = 0;
	int flags = 0;

	while (1) {

		int option_index = 0;
		static struct option long_options[] = {
			{"help", 0, 0, 'h'},
			{"email", 1, 0, 'e'},
			{"password", 1, 0, 'p'},
			{"version", 0, 0, 'v'},
			{"site", 1, 0, 's'},
			{"file", 1, 0, 'f'},
			{"input", 1, 0, 'i'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "he:p:vs:f:i:",
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
			printf("gcookie -f <authfile> -s <site>\n"
			       "Example:  gcookie -f ./.gauthrc -s www.cwxstat.org\n");
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
			snprintf(site, MAXBUF, "%s", optarg);
			break;

		case 'f':
			flags |= 0x40;
			snprintf(file, MAXBUF, "%s", optarg);
			break;

		case 'i':
			flags |= 0x40;
			snprintf(authfile, MAXBUF, "%s", optarg);
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
	if (~flags & 0x10) {
		fprintf(stderr,
			"This program generates a Google cookie\n"
			"from a valid auth token\n"
			"Usage:\n\tgcookie  -s <site>\n"
			"Example:\n\tgcookie -i .gauthrc -s www.cwxstat.org\n");
		exit(2);
	}

	return 1;
}







int main(int argc, char **argv)
{

	mygetopt(argc, argv);

	char *auth = read_auth(authfile);
	if (auth == NULL) {
		fprintf(stderr, "Null auth or file not found\n");
		exit(1);
	}

	char *cookie = parse_cookie(gcookie(auth, site));
	if (cookie != NULL) {
		printf("\n%s\n", cookie);

	}

	return 0;

}
