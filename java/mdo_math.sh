#!/bin/bash
# 
ver=commons-math-2.2
if [ -f repo/${ver}/${ver}.jar ]; then
 echo "${ver}.jar exists... so we will use it!"
else

 echo "Did not find ${ver}.jar so downloading"
 mkdir -p repo
 cd repo
 wget http://download.nextag.com/apache//commons/math/binaries/${ver}.tar.gz
 tar -xzf *.gz
 cd ..
fi
mkdir -p classes
javac -d classes -classpath repo/commons-math-2.2/${ver}.jar ApacheMath.java
java  -classpath repo/commons-math-2.2/${ver}.jar:classes ApacheMath
