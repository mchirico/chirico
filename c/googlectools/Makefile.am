AUTOMAKE_OPTIONS = gnu


lib_LTLIBRARIES = libgooglectools.la
libgooglectools_la_SOURCES = lib/googlectools.c include/_googlectools.h
libgooglectools_la_CFLAGS =  @INCLUDES@ 


include_HEADERS = include/googlectools.h

bin_PROGRAMS = glogin gcookie gauth gpost mytest gauth2 gcookie2 gcal

gcal_SOURCES = src/gcal.c
gcal_LDADD = libgooglectools.la @INCLUDES@

mytest_SOURCES = src/mytest.c 
mytest_LDADD = libgooglectools.la @INCLUDES@




gauth2_SOURCES = src/gauth2.c version.in VERSION
gauth2_LDADD = libgooglectools.la @INCLUDES@

gcookie2_SOURCES = src/gcookie2.c version.in VERSION
gcookie2_LDADD = libgooglectools.la @INCLUDES@

gauth_SOURCES = src/gauth.c version.in VERSION
gauth_LDADD = libgooglectools.la @INCLUDES@

glogin_SOURCES = src/glogin.c version.in VERSION
glogin_LDADD = libgooglectools.la

gcookie_SOURCES = src/gcookie.c version.in VERSION
gcookie_LDADD = libgooglectools.la

gpost_SOURCES = src/gpost.c version.in VERSION
gpost_LDADD = libgooglectools.la

man_MANS = man/glogin.1 man/gcookie.1 

EXTRA_DIST = $(man_MANS) THANKS src/examples/*.c


