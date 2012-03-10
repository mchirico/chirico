/* utmp.c - Dumps raw contents of utmp and wtmp files */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <utmp.h>
#include <popt.h>

void print_utmp_entry(struct utmp *u) {
    struct tm *tp;
    char *type;
    char addrtext[INET6_ADDRSTRLEN];

    switch (u->ut_type) {
        case EMPTY: type = "EMPTY"; break;
        case RUN_LVL: type = "RUN_LVL"; break;
        case BOOT_TIME: type = "BOOT_TIME"; break;
        case NEW_TIME: type = "NEW_TIME"; break;
        case OLD_TIME: type = "OLD_TIME"; break;
        case INIT_PROCESS: type = "INIT_PROCESS"; break;
        case LOGIN_PROCESS: type = "LOGIN_PROCESS"; break;
        case USER_PROCESS: type = "USER_PROCESS"; break;
        case DEAD_PROCESS: type = "DEAD_PROCESS"; break;
        case ACCOUNTING: type = "ACCOUNTING"; break;
    }
    printf("%-13s:", type);
    switch (u->ut_type) {
        case LOGIN_PROCESS:
        case USER_PROCESS:
        case DEAD_PROCESS:
            printf(" line: %s", u->ut_line);
            /* fall through */
        case INIT_PROCESS:
            printf("\n  pid: %6d id: %4.4s", u->ut_pid, u->ut_id);
    }
    printf("\n");
    tp = gmtime(&u->ut_tv.tv_sec);
    printf("  time: %24.24s.%lu\n", asctime(tp), u->ut_tv.tv_usec);
    switch (u->ut_type) {
        case USER_PROCESS:
        case LOGIN_PROCESS:
        case RUN_LVL:
        case BOOT_TIME:
            printf("  user: %s\n", u->ut_user);
    }
    if (u->ut_type == USER_PROCESS) {
        if (u->ut_session)
            printf("  sess: %lu\n", u->ut_session);
        if (u->ut_host)
            printf("  host: %s\n", u->ut_host);
        if (u->ut_addr_v6[0]) {
            if (!(u->ut_addr_v6[1] |
                  u->ut_addr_v6[2] |
                  u->ut_addr_v6[3])) {
                /* only first quad filled in implies IPV4 address */
                inet_ntop(AF_INET, u->ut_addr_v6,
                          addrtext, sizeof(addrtext));
                printf("  IPV4: %s\n", addrtext);
            } else {
                inet_ntop(AF_INET6, u->ut_addr_v6,
                          addrtext, sizeof(addrtext));
                printf("  IPV6: %s\n", addrtext);
            }
        }
    }
    if (u->ut_type == DEAD_PROCESS) {
           printf("  exit: %u:%u\n",
                  u->ut_exit.e_termination,
                  u->ut_exit.e_exit);
    }
    printf("\n");
}

struct utmp * get_next_line(char *id, char *line) {
    struct utmp request;

    if (!id && !line)
        return getutent();

    memset(&request, 0, sizeof(request));

    if (line) {
        strncpy(&request.ut_line[0], line, UT_LINESIZE);
        return getutline(&request);
    }

    request.ut_type = INIT_PROCESS;
    strncpy(&request.ut_id[0], id, 4);
    return getutid(&request);
}

void print_file(char * name, char *id, char *line) {
    struct utmp *u;

    if (utmpname(name)) {
	fprintf(stderr, "utmp database %s open failed\n", name);
	return;
    }
    setutent();
    printf("%s:\n====================\n", name);
    while ((u=get_next_line(id, line))) {
        print_utmp_entry(u);
	/* POSIX requires us to clear the static data before
	 * calling getutline or getutid again
	 */
	memset(u, 0, sizeof(struct utmp));
    }
    endutent();
}

int main(int argc, const char **argv) {
    char *id = NULL, *line = NULL;
    int show_utmp = 1, show_wtmp = 0;
    int c;
    poptContext optCon;
    struct poptOption optionsTable[] = {
        { "utmp", 'u', POPT_ARG_NONE|POPT_ARGFLAG_XOR, 
	   &show_utmp, 0,
          "toggle showing contents of utmp file", NULL },
        { "wtmp", 'w', POPT_ARG_NONE|POPT_ARGFLAG_XOR, 
	   &show_wtmp, 0,
          "toggle showing contents of wtmp file", NULL },
        { "id", 'i', POPT_ARG_STRING, &id, 0,
          "show process entries for specified inittab id", 
	  "<inittab id>" },
        { "line", 'l', POPT_ARG_STRING, &line, 0,
          "show process entries for specified device line", 
	  "<line>" },
        POPT_AUTOHELP
        POPT_TABLEEND
    };

    optCon = poptGetContext("utmp", argc, argv, optionsTable, 0);
    if ((c = poptGetNextOpt(optCon)) < -1) {
        fprintf(stderr, "%s: %s\n",
            poptBadOption(optCon, POPT_BADOPTION_NOALIAS),
            poptStrerror(c));
        return 1;
    }
    poptFreeContext(optCon);

    if (id && line)
        fprintf(stderr, "Cannot choose both by id and line, "
			"choosing by line\n");

    if (show_utmp)
        print_file(_PATH_UTMP, id, line);
    if (show_utmp && show_wtmp)
        printf("\n\n\n");
    if (show_wtmp)
        print_file(_PATH_WTMP, id, line);

    return 0;
}
