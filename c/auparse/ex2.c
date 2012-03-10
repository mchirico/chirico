/*
  gcc ex2.c -o ex2 -lauparse
 */


#include <stdlib.h>
#include <stdio.h>
#include <auparse.h>

main(void)
{

  if (getuid() != 0) {
    fprintf(stderr,"You must be root to run this program\n\n");
    return 0;
  }


  auparse_state_t *au = auparse_init(AUSOURCE_LOGS, NULL);
  
  while (auparse_next_event(au)) {
    if (auparse_first_record(au)) {
      printf("---\n");
      do {/* for each record in this event */
	if (auparse_first_field(au)) {
	  int not_first = 0;
	  do {/* for each field in this record */
	    if (not_first) 
	      printf(" ");
	    else
	      not_first = 1;
	    const char *name = auparse_get_field_name(au);
	    const char *value = auparse_interpret_field(au);
	    if (!name || !value) {
	      printf( "Internal error\n");
	      return 1;
	    }
	    printf("%s = %s",name,value);
	  } while (auparse_next_field(au));
	}
	printf("\n");
      } while (auparse_next_record(au));
    }
  }
  return 0;
}



