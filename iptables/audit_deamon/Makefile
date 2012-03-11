CFLAGS=-g -W -Wall -Wundef
LIBS=
all:
	gcc -c clientlib.c -o clientlib.o
	gcc $(CFLAGS) audisp-logins.c clientlib.o -o audisp-logins $(LIBS)

clean:
	rm -f audisp-logins *.o
