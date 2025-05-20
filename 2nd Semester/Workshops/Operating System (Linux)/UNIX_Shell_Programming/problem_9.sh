#!/bin/bash
#Write a script that finds in a given directory hierarchy, all duplicate files and displays their paths. Hint: use checksums to detect whether two files are identical.

if test -z "$1" || ! test -d "$1"; then
	echo First argument must pe a directory!
	exit 0
fi

#create an asociative array like a map
declare -A check
for file in $(find $1 -type f); do
	hash=$(sha1sum $file | awk '{print $1}')
	if test -n "${check[$hash]}"; then
		echo Duplicate file detected PATH : $file with ${check[$hash]}
	else
		check[$hash]=$file
	fi
done