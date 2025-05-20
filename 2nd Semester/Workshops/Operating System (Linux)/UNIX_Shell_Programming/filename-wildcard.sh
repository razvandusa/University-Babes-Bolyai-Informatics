#!/bin/bash
#Count all the lines of code in the C files in the directory given as command line argument, excluding lines that are empty or contain only spaces

S=0
for file in $1/*.c; do
	N=`grep -E -v "^$" $file | wc -l`
	S=`expr $S + $N`
done
echo $S
