#!/bin/bash
#Find recursively in a directory, all the files that have write permissions for everyone. Display their names, and the permissions before and after removing the write permission for everybody. You will need to use chmod's symbolic permissions mode, instead of the octal mode we have used in class. The the chmod manual for details.

if test -z "$1" || ! test -d "$1"; then
	echo First argument must be a directory!
fi

for file in $(find $1 -type f); do
	permisions=$(ls -l $file | awk '{print $1" "$9}')
	echo $permisions
	chmod o-w $file
	permisions=$(ls -l $file | awk '{print $1" "$9}')
	echo $permisions
done