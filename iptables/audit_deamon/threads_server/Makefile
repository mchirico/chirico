# Version
VERSION = 0.1.0

# Compiler flags
MYNOLINK = -Wall -W -O2 -s -pipe 
CFLAGS = -Wall -W -O2 -s -pipe -lpthread 
SPFLAGS = -Wall -W -O2 -s -pipe -lpthread  -ldl

all: threads_server_sqlite client


threads_server_sqlite: src/threads_server.c wrapper
	  gcc  -o threads_server wrapper.o   $(CFLAGS)  $<

client: src/client.c wrapper
	  gcc -o client wrapper.o  $(CFLAGS)  $<

wrapper: src/wrapper.c
	  gcc -c -o wrapper.o $(MYNOLINK)  $<

clean:	
	rm -f threads_server client  wrapper.o


