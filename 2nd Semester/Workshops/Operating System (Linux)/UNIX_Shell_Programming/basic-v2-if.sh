#!/bin/bash

for arg in $@; do
	if [ -f $arg ]; then
		echo $arg is a file!
	elif [ -d $arg ]; then
		echo $arg is a directory!
	elif echo $arg | grep -E -q "^[0-9]+$"; then
		echo $arg is a number!
	else
	       	echo We do not know what $arg is!
	fi
done