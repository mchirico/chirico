/*

    gcc uuid.c -luuid

    You probably only want to run uuidgen

 */


#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>

int main(void) {

  uuid_t u;
  char str[37];
  uuid_generate_time(u);
  uuid_unparse(u, str);

  fprintf(stderr,"%s\n",str);

  return 0;
}

/*
void uuid_generate(uuid_t out);
void uuid_generate_random(uuid_t out);
void uuid_generate_time(uuid_t out);
*/
