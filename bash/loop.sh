#!/bin/bash
for i in c*
do 
   if [[ $i != "check_dsm" ]]
   then
           echo ${i}
   fi

done