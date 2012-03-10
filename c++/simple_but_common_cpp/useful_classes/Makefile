# Version
VERSION = 0.0.1

# Compiler flags
CFLAGS = -Wall -W -O2 -s -pipe
SL3FLAGS = -Wall -W -O2 -s -pipe -Wl,-R/usr/local/lib -lsqlite3
sqlite3LIB := $(shell ls /usr/local/lib/libsqlite3.so)

all: extract simplesqlite3cpp2 sqlite3api

extract: extract.cc extract.h
	  g++ -o $@ $(CFLAGS)  $<


simplesqlite3cpp2: simplesqlite3cpp2.cc
ifeq ("$(sqlite3LIB)","/usr/local/lib/libsqlite3.so")
	g++ -o $@ $(SL3FLAGS)  $<
else
	echo "Where is sqlite version 3? I looked for /usr/local/lib/libsqlite3.so"
endif

sqlite3api: sqlite3api.cc mysqlite3.h
ifeq ("$(sqlite3LIB)","/usr/local/lib/libsqlite3.so")
	g++ -o $@ $(SL3FLAGS)  $<
else
	echo "Where is sqlite version 3? I looked for /usr/local/lib/libsqlite3.so"
endif




clean:	
	rm -f  extract simplesqlite3cpp2 sqlite3api


