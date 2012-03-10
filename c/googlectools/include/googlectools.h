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

#ifndef GOOGLEAUTH_H
#define GOOGLEAUTH_H

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
extern int errno;

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#include "version.h"


char *gauth(const char *email, const char* passwd, const char* service);


char *gcookie(char *auth, const char* site);
char *gxcookie(char *auth, const char* site);

char *gxauth(const char *auth);
char *giauth(const char *auth);
char *gspread(const char *auth);
char *gcal(const char *auth);



char *parse_cookie(char *);


#endif
