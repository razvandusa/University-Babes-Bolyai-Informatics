#!/bin/bash
#Display the session count and full names of all the users who logged into the system this month, sorting the output by the session count in descending order. Use the -s and/or -t options of command last to get this month's sessions, and the command date to generate the required timestamp in the expected format.

month="$(date | awk '{print $2}')"
year="$(date | awk '{print $6}')"

if test "$month" == "Jan"; then
	month=1
elif test "$month" == "Feb"; then
	month=2
elif test "$month" == "Mar"; then
        month=3
elif test "$month" == "Apr"; then
        month=4
elif test "$month" == "May"; then
        month=5
elif test "$month" == "Jun"; then
        month=6
elif test "$month" == "Jul"; then
        month=7
elif test "$month" == "Aug"; then
        month=8
elif test "$month" == "Sep"; then
        month=9
elif test "$month" == "Oct"; then
        month=10
elif test "$month" == "Nov"; then
        month=11
elif test "$month" == "Dec"; then
        month=12
fi

users=$(last -s "$year-$month-1" | sed -E "s/\(/ /g" | sed -E "s/\)/ /g" | awk '
$10~"[0-9]+"{print $1" "$10}' | head -n -2 | sort -k2 -r)

while read -r line; do
	echo $line
done <<< $users