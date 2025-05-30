#!/bin/bash
#Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files.

found=0
for file in $(find . -iregex ".*\.c"); do
	lines=$(grep -v -c -E "^$" $file)
	if test $lines -gt 500 && test $found -lt 2; then
		found=$(($found + 1))
		echo $file
	fi
done