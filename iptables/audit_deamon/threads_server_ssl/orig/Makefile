
CC = gcc
CFLAGS = -g -Wall -pthread
LFLAGS = -lssl -lcrypto
RM = /bin/rm
CAT = /bin/cat
OPENSSL = /usr/bin/openssl


OBJS = reentrant.o	\
       common.o		\
       client.o		\
       server.o		\
       client1.o	\
       server1.o	\
       client2.o	\
       server2.o	\
       client3.o	\
       server3.o

BINS = client server client1 server1 client2 server2 client3 server3

CERTS = root.pem serverCA.pem server.pem client.pem

DHPARAMS = dh512.pem dh1024.pem

all: $(CERTS) $(DHPARAMS) $(BINS)

$(BINS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(@).o common.o reentrant.o $(LFLAGS)

$(OBJS): common.h reentrant.h

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(CERTS): $(CERTS:.pem=.cnf)
	$(OPENSSL) req -newkey rsa:1024 -sha1 -keyout rootkey.pem -out rootreq.pem -config root.cnf
	$(OPENSSL) x509 -req -in rootreq.pem -sha1 -extfile root.cnf -extensions certificate_extensions -signkey rootkey.pem -out rootcert.pem
	$(CAT) rootcert.pem rootkey.pem > root.pem
	$(OPENSSL) req -newkey rsa:1024 -sha1 -keyout serverCAkey.pem -out serverCAreq.pem -config serverCA.cnf
	$(OPENSSL) x509 -req -in serverCAreq.pem -sha1 -extfile serverCA.cnf -extensions certificate_extensions -CA root.pem -CAkey root.pem -CAcreateserial -out serverCAcert.pem
	$(CAT) serverCAcert.pem serverCAkey.pem rootcert.pem > serverCA.pem
	$(OPENSSL) req -newkey rsa:1024 -sha1 -keyout serverkey.pem -out serverreq.pem -config server.cnf -reqexts req_extensions
	$(OPENSSL) x509 -req -in serverreq.pem -sha1 -extfile server.cnf -extensions certificate_extensions -CA serverCA.pem -CAkey serverCA.pem -CAcreateserial -out servercert.pem
	$(CAT) servercert.pem serverkey.pem serverCAcert.pem rootcert.pem > server.pem
	$(OPENSSL) req -newkey rsa:1024 -sha1 -keyout clientkey.pem -out clientreq.pem -config client.cnf -reqexts req_extensions
	$(OPENSSL) x509 -req -in clientreq.pem -sha1 -extfile client.cnf -extensions certificate_extensions -CA root.pem -CAkey root.pem -CAcreateserial -out clientcert.pem
	$(CAT) clientcert.pem clientkey.pem rootcert.pem > client.pem

certclean:
	$(RM) -f rootkey.pem rootreq.pem rootcert.pem root.pem root.srl
	$(RM) -f serverCAkey.pem serverCAreq.pem serverCAcert.pem serverCA.pem serverCA.srl
	$(RM) -f serverkey.pem serverreq.pem servercert.pem server.pem
	$(RM) -f clientkey.pem clientreq.pem clientcert.pem client.pem

dh512.pem:
	$(OPENSSL) dhparam -check -text -5 512 -out dh512.pem

dh1024.pem:
	$(OPENSSL) dhparam -check -text -5 1024 -out dh1024.pem

dhparamclean:
	$(RM) -f $(DHPARAMS)

clean:
	$(RM) -f $(BINS) $(OBJS) *~

distclean: clean certclean dhparamclean
