/* pamexample.c - Simple example of authentication using PAM */

/* The pamexample program demonstrates some simple PAM handling.
 * You will either have to use the --service command line option
 * to choose a service name that is already installed ("system-auth"
 * may work, check for /etc/pam.d/system-auth on your system), or
 * install a system file * /etc/pam.d/pamexample with the following
 * four lines (ignoring leading "*" characters):
 * #%PAM-1.0
 * auth         required    /lib/security/pam_unix.so
 * account	required    /lib/security/pam_unix.so
 * session      required    /lib/security/pam_limits.so
 *
 * Note that if you run this program as a non-root user, there
 * may be system limitations on what you can do; account management
 * may fail, you may not be able to test other users' passwords,
 * and session management may fail, all depending on how the
 * service is configured.
 */

#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <popt.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* This struct can be an automatic, but it must not go out
 * of scope between pam_start() and pam_end(), so it is
 * easier in simple programs to make it a static instead
 */
static struct pam_conv my_conv = {			    
    misc_conv, /* use TTY conversation function from libpam_misc */
    NULL       /* we have no special data to pass to misc_conf */
};							    

void check_success(pam_handle_t *pamh, int return_code) {
    if (return_code != PAM_SUCCESS) {
	fprintf(stderr, "%s\n", pam_strerror(pamh, return_code));
	exit(1);
    }
}

int main(int argc, const char **argv) {
    pam_handle_t *pamh;
    struct passwd *pw;
    char *username=NULL, *service=NULL;
    int account = 1, session = 0;
    int c;
    poptContext optCon;
    struct poptOption optionsTable[] = {
        { "username", 'u', POPT_ARG_STRING, &username, 0,
          "Name of user to authenticate", "<username>" },
        { "service", 'S', POPT_ARG_STRING, &service, 0,
          "Name of service to initialize as (pamsample)", 
	  "<service>" },
        { "account", 'a', POPT_ARG_NONE|POPT_ARGFLAG_XOR, 
	  &account, 0,
          "toggle whether to do account management (on)", "" },
        { "session", 's', POPT_ARG_NONE|POPT_ARGFLAG_XOR, 
	  &session, 0,
          "toggle whether to start a session (off)", "" },
        POPT_AUTOHELP
        POPT_TABLEEND
    };

    optCon = poptGetContext("pamexample", argc, argv, 
			    optionsTable, 0);
    if ((c = poptGetNextOpt(optCon)) < -1) {
        fprintf(stderr, "%s: %s\n",
            poptBadOption(optCon, POPT_BADOPTION_NOALIAS),
            poptStrerror(c));
        return 1;
    }
    poptFreeContext(optCon);

    if (!service) {
	/* Note that a normal application must not give this
	 * option to the user; it exists here to make it
	 * possible to test this application without making
	 * system changes requiring root access.
	 */
	service = "pamexample";
    }

    if (!username) {
	/* default to current user */
        if (!(pw = getpwuid(getuid()))) {
            fprintf(stderr, "Username does not exist");
	    exit(1);
	}
	username = strdup(pw->pw_name);
    }

    c = pam_start(service, username, &my_conv, &pamh);	
    check_success(pamh, c);

    c = pam_authenticate(pamh, 0);			
    check_success(pamh, c);

    if (account) {
	/* if authentication did not succeed, account management
	 * is not defined
	 */
	c = pam_acct_mgmt(pamh, 0);			
	check_success(pamh, c);
    }

    if (session) {
	/* We would fork here if we were going to fork */
	c = pam_open_session(pamh, 0);			
	check_success(pamh, c);

        /* Note that this will not set uid, gid, or supplemental 
	   groups */
	c = pam_setcred(pamh, 0);                       

	/* We would drop permissions here if we were going to */

	/* Call a shell that has been "authenticated" */
	printf("Running shell...\n");
	system("exec bash -");

	/* We would wait4() here if we had forked instead of 
	   calling system() */
	c = pam_close_session(pamh, 0);			
	check_success(pamh, c);
    }

    /* Real applications would report failure instead of
     * bailing out as we do in check_success at each stage,
     * so c might be something other than PAM_SUCCESS in
     * those cases.
     */
    c = pam_end(pamh, c);				
    check_success(pamh, c);

    return 0;
}
