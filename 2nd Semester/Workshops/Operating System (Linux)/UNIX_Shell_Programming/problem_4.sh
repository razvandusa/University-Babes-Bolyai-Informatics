#!/bin/bash
#Find recursively in a given directory all the symbolic links, and report those that point to files/directories that no longer exist. Use operator -L to test if a path is a symbolic link, and operator -e to test if it exists (will return false if the target to which the link points does not exist)

if test -z "$1" || ! test -d "$1"; then
	echo First argument must be a directory!
	exit 0
fi

for simboliclink in $(find $1 -type l); do
	if ! test -e "$simboliclink"; then
		echo $simboliclink points to files/directories that not longer exist!
	fi
done