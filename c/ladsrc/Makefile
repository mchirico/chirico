CFLAGS = -Wall 
LDFLAGS = -g
CC = gcc

TARGETS = ladsh4 ladsh3 ladsh2 ladsh1 sighup mknod dircontents broken \
	  globit mpx-blocks mpx-nonblock statsamp calc popenglob robin \
	  mpx-select map-cat ptytest forkptytest lock userver \
	  uclient queued catch-segv grep popt-nest find \
	  lookup minopen services tserver tclient gather passfd id \
	  ladsh4 monitor checkflags setflags usehello loadhello readpass cat \
	  match select-vs-poll mpx-poll itimer utmp pamexample leases \
	  dirchange bufferoverflow qdbmsimple phones sicode netlookup \
	  clientlookup serverlookup reverselookup tftpserver mpx-epoll \
	  poll-vs-epoll
POPT = -lpopt
UTIL = -lutil

all: $(TARGETS) 

ptytest: ptytest.c ptypair.c

forkptytest: forkptytest.c $(UTIL)

qdbmsimple: qdbmsimple.c 
	$(CC) $(CFLAGS) -o qdbmsimple qdbmsimple.c -lqdbm $(LDFLAGS)

phones: phones.c
	$(CC) $(CFLAGS) -o phones phones.c -lqdbm $(LDFLAGS)

robin: robin.c $(POPT)

grep: grep.c $(POPT)

utmp: utmp.c $(POPT)

popt-nest: popt-nest.c popt-lib.c $(POPT)

pamexample: pamexample.c $(POPT)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -lpopt -lpam -lpam_misc -ldl

userver: userver.c sockutil.o

uclient: uclient.c sockutil.o

tserver: tserver.c sockutil.o

tclient: tclient.c sockutil.o

passfd: passfd.c sockutil.o

tftpserver: tftpserver.c sockutil.o

libhello.o: libhello.c
	@echo "*  Use -fPIC to build an object file for a shared library."
	$(CC) -fPIC $(CFLAGS) -c $<

libhello.so.0.0:	libhello.o
	@echo "*  Link libhello against libc for best results on all systems."
	$(CC) $(LDFLAGS) -shared -Wl,-soname,libhello.so.0 -o $@ $< -lc
	@echo "*  Create a pointer from the soname to the library."
	ln -sf libhello.so.0.0 libhello.so.0
	@echo "*  Create a pointer for the linker."
	ln -sf libhello.so.0 libhello.so

usehello: usehello.o libhello.so.0.0
	@echo "*  -L. -lhello, not libhello.so.0"
	$(CC) $(LDFLAGS) -o $@ $< -L. -lhello
	@echo "*  Now run: LD_LIBRARY_PATH=`pwd` ./$@"

loadhello: loadhello.o libhello.so.0.0
	$(CC) $(LDFLAGS) -o $@ $< -ldl
	@echo "Now run: LD_LIBRARY_PATH=`pwd` ./$@"

clean:
	rm -f $(TARGETS) *.o libhello.so*

