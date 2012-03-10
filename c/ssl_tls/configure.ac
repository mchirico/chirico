#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(src/tlssmtp.c,[],[mchirico@users.sourceforge.net])
#CFLAGS='-Wall -W -O2 -lssl -lcrypt'
CFLAGS='-Wall -W -O2'


if test -f VERSION; then
  VERSION=`cat VERSION`
  echo "Version set to $VERSION"
else
  VERSION='0.0.0'
fi
AM_INIT_AUTOMAKE(ssl_tls, $VERSION )



# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lfl':
AC_CHECK_LIB([fl], [main])
AC_CHECK_LIB([ssl], [main])
AC_CHECK_LIB([crypto], [main])


# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h ])
# OpenSSL current
AC_CHECK_HEADERS([openssl/bio.h openssl/x509v3.h openssl/rand.h openssl/err.h ])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

INCLUDES="$INCLUDES -I/usr/local/include"

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
