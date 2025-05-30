#!/bin/bash
#Find recursively in a directory, all the files with the extension ".log" and sort their lines (replace the original file with the sorted content).

if test -z "$1" || ! test -d "$1"; then
	echo First arguments must be a directory!
	exit 0
fi

for file in $(find $1 -iregex ".*\.log"); do
	sort $file -o $file
done