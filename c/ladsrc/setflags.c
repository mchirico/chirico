/* setflags.c - Sets values of ext3 extended attributes */

/* The first parameter to this program is a string consisting of
   0 (an empty string is okay) or more of the letters I, A, S, and
   N. This string specifies which ext3 attributes should be turned
   on for the files which are specified on the rest of the command
   line -- the rest of the attributes are turned off. The letters
   stand for immutable, append-only, sync, and nodump, respectively.

   For example, the command "setflags IN file1 file2" turns on the
   immutable and nodump flags for files file1 and file2, but turns
   off the sync and append-only flags for those files. */

#include <errno.h>
#include <fcntl.h>
#include <linux/ext3_fs.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, const char ** argv) {
    const char ** filename = argv + 1;
    int fd;
    int flags = 0;
    
    /* Make sure the flags to set were specified, along with
       some file names. Allow a "0" to be set to indicate that all
       of the flags should be reset. */
    if (argc < 3) {
        fprintf(stderr, "setflags usage: [0][I][A][S][N] "
	                "<filenames>\n");
        return 1;
    }

    /* each letter represents a flag; set the flags which are 
       specified */
    if (strchr(argv[1], 'I')) flags |= EXT3_IMMUTABLE_FL;
    if (strchr(argv[1], 'A')) flags |= EXT3_APPEND_FL;
    if (strchr(argv[1], 'S')) flags |= EXT3_SYNC_FL;
    if (strchr(argv[1], 'N')) flags |= EXT3_NODUMP_FL;
    
    /* iterate over all of the file names in argv[] */
    while (*(++filename)) {
        /* Unlike normal attributes, ext3 attributes can only
           be set if we have a file descriptor (a file name
           isn't sufficient). We don't need write access to set
           the ext3 attributes, so O_RDONLY is fine. */
        fd = open(*filename, O_RDONLY);
        if (fd < 0) {
            fprintf(stderr, "cannot open %s: %s\n", *filename,
                    strerror(errno));
            return 1;
        }

        /* Sets the attributes as specified by the contents of
           flags. */
        if (ioctl(fd, EXT3_IOC_SETFLAGS, &flags)) {
            fprintf(stderr, "ioctl failed on %s: %s\n", *filename,
                    strerror(errno));
            return 1;
        }
        close(fd);
    } 

    return 0;
};
