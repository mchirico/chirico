#!/bin/bash
openssl rsa -in clientkey.pem -out clientkey.pem.ins
cat clientcert.pem clientkey.pem.ins rootcert.pem > client.pem

openssl rsa -in serverkey.pem -out serverkey.pem.ins
cat servercert.pem serverkey.pem.ins serverCAcert.pem rootcert.pem > server.pem
