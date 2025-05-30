#!/bin/bash

D=$1
S=$2
for file in `find $D -type f`; do
	sizeOfFile=`du -b $file | awk '{print $1}'`
	if test $sizeOfFile -gt $S; then
		echo "$file has `du -b $file | awk '{print $1}'` bytes"
	fi
done