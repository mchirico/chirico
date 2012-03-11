#!/bin/bash
while (true)
do
 ping -D -i 5 -c 34000 74.125.226.144 >> data
 date >> data
 rm -f data.2
 mv data.1 data.2
 mv data data.1
done
