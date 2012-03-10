AUTOMAKE_OPTIONS = gnu

bin_PROGRAMS = tlsimap tlsserver sslpop3 tlssmtp

tlsimap_SOURCES = src/tlsimap.c 
tlsserver_SOURCES = src/tlsserver.c
sslpop3_SOURCES = src/sslpop3.c
tlssmtp_SOURCES = src/tlssmtp.c

man_MANS = man/tlsimap.1 man/tlsserver.1 man/tlstutorial.1

EXTRA_DIST = $(man_MANS) VERSION  scripts/smtp_scripts.pl scripts/Notes
