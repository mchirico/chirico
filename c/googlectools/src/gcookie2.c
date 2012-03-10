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

#include "googlectools.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv)
{

	if (argc != 4) {
		fprintf(stderr, "Enter usename, password, site\n");
		return 0;
	}


	char *auth = gauth(argv[1], argv[2],"ah");
	if (auth != NULL) {
		printf("%s\n", auth);
		char *cookie = gcookie(auth, argv[3]);
		if (cookie != NULL) {
			printf("cookie returned: %s\n", cookie);

			fprintf(stderr, "%s\n",
				post("dev.mchirico.org",
				     "/cron/fireAction",
				     parse_cookie(cookie), ""));
			char *xcookie = gxcookie(auth, argv[3]);
			fprintf(stderr, "cookie expired: %s\n", xcookie);


		}

	}


	return 0;


}
