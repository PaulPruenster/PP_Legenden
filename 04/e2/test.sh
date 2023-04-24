#!/bin/sh
i=0
while [ $i -ne 1000 ]
do
        i=$(($i+1))
        ./flush
        printf "$i\n"
done