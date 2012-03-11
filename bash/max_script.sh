#!/bin/bash
function max ()
{
    if [ $1 -gt $2 ]
    then
	echo $1
    else
	echo $2
    fi
}

r=$(max 3 55)
echo $r
