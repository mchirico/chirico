/*
  gcc ex4.c -o ex4 -lauparse

This example is not working
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <auparse.h>

void
auparse_callback(auparse_state_t * au, auparse_cb_event_t cb_event_type,
                 void *user_data)
{
        int *event_cnt = (int *) user_data;

        if (cb_event_type == AUPARSE_CB_EVENT_READY) {
                if (auparse_first_record(au) <= 0)
                        return;
                printf("event: %d\n", *event_cnt);
                printf("records:%d\n", auparse_get_num_records(au));
                do {
                        printf("fields:%d\n", auparse_get_num_fields(au));
                        printf("type=%d ", auparse_get_type(au));
                        const au_event_t *e = auparse_get_timestamp(au);
                        if (e == NULL)
                                return;
                        printf("event time: %u.%u:%lu\n",
                               (unsigned) e->sec, e->milli, e->serial);
                        auparse_first_field(au);
                        do {
                                printf("%s=%s (%s)\n",
                                       auparse_get_field_name(au),
                                       auparse_get_field_str(au),
                                       auparse_interpret_field(au));
                        } while (auparse_next_field(au) > 0);
                        printf("\n");

                } while (auparse_next_record(au) > 0);
                (*event_cnt)++;
        }
}

main(int argc, char **argv)
{
        char *filename = argv[1];
        FILE *fp;
        char buf[256];
        size_t len;
        int *event_cnt = malloc(sizeof(int));


        auparse_state_t *au = auparse_init(AUSOURCE_LOGS, NULL);


        *event_cnt = 1;
        auparse_add_callback(au, auparse_callback, event_cnt, free);

        if ((fp = fopen(filename, "r")) == NULL) {
                fprintf(stderr,
                        "could not open %s filename", strerror(errno));
               return 1;
           }

           while ((len = fread(buf, 1, sizeof(buf), fp))) {
               auparse_feed(au, buf, len);
           }
           auparse_flush_feed(au);
}



