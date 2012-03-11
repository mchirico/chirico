#!/bin/bash
# Source: http://chirico.googlecode.com/svn/trunk/bash/pingtest/pingtest.sh
export DATADIR=/var/www/apachefiles/
while (true)
do
 ping -D -i 5 -c 340000 74.125.226.144 >> ${DATADIR}data
 date >> ${DATADIR}data
 rm -f ${DATADIR}data.2
 mv ${DATADIR}data.1 ${DATADIR}data.2
 mv ${DATADIR}data ${DATADIR}data.1
done
