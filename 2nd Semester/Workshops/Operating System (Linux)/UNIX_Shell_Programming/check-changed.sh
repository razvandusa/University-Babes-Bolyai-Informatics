#!/bin/bash
#Write a script that monitors the state of a directory and prints a notification when something changed

if test -z "$1" || ! test -d "$1"; then
	echo First argument needs to be a directory!
fi

Before=""
while true; do
	After=""
	for file_or_directory in $(find $1); do
		if test -f "$file_or_directory"; then
			content=$(ls -l $file_or_directory | sha1sum)
		elif test -d "$file_or_directory"; then
			content=$(ls -l -d $file_or_directory | sha1sum)
		fi
		After="$After\n$content"
	done
	if test -n "$Before" && test "$Before" != "$After"; then
		echo Directory state changed
	fi
	Before="$After"
	sleep 1
done