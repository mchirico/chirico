#!/bin/bash
# gcc delete.c -o d
for i in `seq 1 10000`;
        do
                ./d
		echo $i
		sleep 20
        done    
