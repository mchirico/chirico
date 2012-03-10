#!/bin/bash
gcc `xml2-config --cflags --libs` -o xmlstory xmlstory.c
gcc `xml2-config --cflags --libs` -o xmladdkey xmladdkey.c
gcc `xml2-config --cflags --libs` -o xmladdatt xmladdatt.c
gcc `xml2-config --cflags --libs` -g -o xml1 xml1.c
gcc `xml2-config --cflags --libs` -g -o test test.c
#./xmlstory story.xml
#./xmladdkey story.xml garbo
#./xmladdatt story.xml attgarbo
#valgrind --leak-check=yes ./xml1 story.xml xml1
valgrind --leak-check=yes ./test

