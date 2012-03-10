#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(open.c)



if test -f VERSION; then
  VERSION=`cat VERSION`
  echo "Version set to $VERSION"
else
  VERSION='0.0.0'
fi
AM_INIT_AUTOMAKE(simple_but_common, $VERSION )



# Checks for programs.
# Below is only for C++ programs
#AC_PROG_CXX


# Checks for libraries.
# FIXME: Replace `main' with a function in `-lfl':
AC_CHECK_LIB([fl], [main])

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

INCLUDES="$INCLUDES -I/usr/local/include"

# Flags for all errors
CFLAGS="-Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings"


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
