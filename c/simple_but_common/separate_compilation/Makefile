# Version
VERSION = 0.0.1

# Compiler flags
CFLAGS = -Wall -W -O2 -s -pipe

all: stuff_user user.o stuff.o
	g++ $(CFLAGS)  -o user user.o stuff.o 

stuff_user: stuff.c user.c
	  g++ $(CFLAGS) -c  stuff.c user.c 



clean:	
	rm stuff.o user.o user


