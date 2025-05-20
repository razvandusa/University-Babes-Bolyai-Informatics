#!/bin/bash
#Count all the lines in the C files in the directory given as command line argument and its subdirectories, excluding lines that are empty or contain only spaces

S=0
for file in `find $1 -type f -iregex ".*.c"`; do
	N=`grep -E -v "^$" $file | wc -l`
	S=`expr $S + $N`
done
echo $S

