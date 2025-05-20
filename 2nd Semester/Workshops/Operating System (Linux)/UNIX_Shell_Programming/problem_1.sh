#!/bin/bash
#Display a report showing the full name of all the users currently connected, and the number of processes belonging to each of them.

for people in $(awk '{print $1}' who.fake); do
	num=$(grep -c -E "^$people" ps.fake)
	echo $people $num
done