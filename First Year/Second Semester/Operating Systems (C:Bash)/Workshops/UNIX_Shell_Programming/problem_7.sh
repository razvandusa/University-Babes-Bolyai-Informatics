#!/bin/bash
#Consider a file containing a username on each line. Generate a comma-separated string with email addresses of the users that exist. The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username. Make sure the generated string does NOT end in a comma.

if test -z "$1" || ! test -f "$1"; then
	echo First argument must be a file!
fi

output=""
while read -r username;do
	if test -z $output; then
		output="$username@scs.ubbcluj.ro"
	else
		output="$output,$username@scs.ubbcluj.ro"
	fi
done < $1
echo $output