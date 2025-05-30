#!/bin/bash
#Write a script that receives dangerous program names as command line arguments. The script will monitor all the processes in the system, and whenever a program known to be dangerous is run, the script will kill it and display a message

while true; do
	for arg in $@; do
		pid=$(ps -ef | grep "\./$arg" | grep -v "grep" | head -n 1 | awk '{print $2}')
		if test -n "$pid" && kill -9 $pid; then
			echo Killed the process $arg because it is dangerous!
		fi
	done
done