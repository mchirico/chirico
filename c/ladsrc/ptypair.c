/* ptypair.c - Allocate a matched pair of pty devices */

#define _XOPEN_SOURCE 600
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/* get_master_pty() takes a double-indirect character pointer in 
 * which to put a slave name, and returns an integer file 
 * descriptor. If it returns < 0, an error has occurred. Otherwise, 
 * it has returned the master pty file descriptor, and fills in 
 * *name with the name of the corresponding slave pty. Once the 
 * slave pty has been opened, you are responsible to free *name.
 */

int get_master_pty(char **name) { 
    int i, j;
    /* default to returning error */
    int master = -1;
    char *slavename;

    master = open("/dev/ptmx", O_RDWR);
    /* This is equivalent to, though more widely implemented but
     * theoretically less portable than:
     * master = posix_openpt(O_RDWR);
     */

    if (master >= 0 && grantpt (master) >= 0 && 
		       unlockpt (master) >= 0) {
        slavename = ptsname(master);
        if (!slavename) {
            close(master);
            master = -1;
            /* fall through to fallback */
        } else {
            *name = strdup(slavename);
            return master;
        }
    }

    /* The rest of this function is a fallback for older systems */

    /* create a dummy name to fill in */
    *name = strdup("/dev/ptyXX");

    /* search for an unused pty */
    for (i=0; i<16 && master <= 0; i++) {
        for (j=0; j<16 && master <= 0; j++) {
            (*name)[8] = "pqrstuvwxyzPQRST"[i];
            (*name)[9] = "0123456789abcdef"[j];
            /* open the master pty */
            if ((master = open(*name, O_RDWR)) < 0) {
                if (errno == ENOENT) {
                    /* we are out of pty devices */
                    free (*name);
                    return (master);
                }
            }
        }
    }

    if ((master < 0) && (i == 16) && (j == 16)) {
        /* must have tried every pty unsuccessfully */
        free (*name);
        return (master);
    }

    /* By substituting a letter, we change the master pty
     * name into the slave pty name.
     */
    (*name)[5] = 't';

    return (master);
}

/* get_slave_pty() returns an integer file descriptor.
 * If it returns < 0, an error has occurred.
 * Otherwise, it has returned the slave file descriptor.
 */

int get_slave_pty(char *name) { 
    struct group *gptr;
    gid_t gid;
    int slave = -1;

    if (strcmp(name, "/dev/pts/")) {
        /* The Unix98 interface has not been used, special
         * permission or ownership handling is necessary.
         * 
         * chown/chmod the corresponding pty, if possible.
         * This will work only if the process has root permissions.
         * Alternatively, write and exec a small setuid program 
         * that does just this.
         *
         * Alternatively, just ignore this and use only the Unix98
         * interface.
         */
        if ((gptr = getgrnam("tty")) != 0) {
            gid = gptr->gr_gid;
        } else {
            /* if the tty group does not exist, don't change the
             * group on the slave pty, only the owner
             */
            gid = -1;
        }

        /* Note that we do not check for errors here.  If this is 
	 * code where these actions are critical, check for errors!
         */
        chown(name, getuid(), gid);

        /* This code makes the slave read/writeable only for the 
	 * user. If this is for an interactive shell that will 
	 * want to receive "write" and "wall" messages, OR S_IWGRP 
	 * into the second argument below.  In that case, you will 
	 * want to move this line outside the if() clause so that 
	 * it is run for * both BSD-style and Unix98-style 
	 * interfaces.
         */
        chmod(name, S_IRUSR|S_IWUSR);
    }

    /* open the corresponding slave pty */
    slave = open(name, O_RDWR);

    return (slave);
}
