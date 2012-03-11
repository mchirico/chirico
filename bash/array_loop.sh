#!/bin/bash
declare -a A
CMD=$(ls -l)
A=($CMD)
for ((i=0; i<${#A[@]}; i++))
do
echo ${A[$i]}
done

