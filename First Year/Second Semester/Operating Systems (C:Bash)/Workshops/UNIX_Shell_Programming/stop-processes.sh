#!/bin/bash
#Stop student processes older than the number of seconds given as command line argument.

S=$1
while read -r line; do
	if echo $line | awk '{print $7}'| grep -q -E "^([0-9][0-9]:){2}[0-9]{2}$"; then
		time=$(echo $line | awk '{print $7}')
		ore=$((${time:0:1} * 10 + ${time:1:1}))
		minute=$((${time:3:1} * 10 + ${time:4:1}))
		secunde=$((${time:6:1} * 10 + ${time:7:1}))
		total_secunde=$(($ore * 3600 + $minute * 60 + $secunde))
		if test $total_secunde -gt $S ; then
			echo Should kill process $(echo $line | awk '{print $2}')
		fi
	fi
done < ps.fake