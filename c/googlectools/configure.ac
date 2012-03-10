#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(src/glogin.c)
AC_PROG_LIBTOOL


if test -f VERSION; then
  VERSION=`cat VERSION`
  echo "Version set to $VERSION"
else
  VERSION='0.0.0'
fi

AM_INIT_AUTOMAKE(googlectools, $VERSION)

# Flags for all errors
CFLAGS="-Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings"
# Debugging Use this for Valgrind
# CFLAGS="-g -O0 -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings"


# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL



# Checks for libraries.
# FIXME: Replace `main' with a function in -lcrypto -lssl
AC_CHECK_LIB([crypto], [main])
AC_CHECK_LIB([ssl], [main])




# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h openssl/bio.h openssl/x509v3.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

INCLUDES="$INCLUDES -I/usr/local/include -Iinclude"

AC_SUBST(INCLUDES)
AC_CONFIG_FILES([include/version.h:version.in])         # File must be renamed
AC_OUTPUT(Makefile)

echo "

  googlectools Version:     $VERSION
  Target:                 $target
  Installation prefix:    $prefix
  Compiler:               $CC
  Compiler flags:
`echo $CFLAGS | fmt -w 50 | sed 's,^,                          ,'`
"

