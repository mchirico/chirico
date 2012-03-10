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

#ifndef _GOOGLECTOOLS_H
#define _GOOGLECTOOLS_H

static char *_gauth(const char *email, const char *passwd, char *auth,const char *service);
static char *_gxauth(const char *auth);
static char *_giauth(const char *auth);
static char *_gspread(const char *auth);
static char *_gcal(const char *auth);

static char *raw_http(int sockfd,const char *rawdata);



static char *_gcookie(char *auth, const char *site);
static char *_gxcookie(char *auth, const char *site);

static char *_post(char *hname, char *page, char *cookie, char *poststr);

static char *parse_cookie_file(char *);
int write_cookie(char *t, const char *rcfile);

static char *process_http(int sockfd, char *host, char *page,
			  char *poststr);
static char *process_post(int sockfd, char *cookie, char *host, char *page,
			  char *poststr);





#endif
