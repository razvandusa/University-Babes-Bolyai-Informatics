#!/bin/bash
#Display all the mounted file systems who are either smaller than than 1GB or have less than 20% free space.

for line in $(cat ./df.fake | tail -n +2 | awk '{print $6":"$2":"$5}'); do
	disk_memory_usage=$(echo $line | awk -F: '{print $2}' | sed "s/M/ /")
	disk_percentage_usage=$(echo $line | awk -F: '{print $3}' | sed "s/%/ /")
	if test $disk_memory_usage -lt 1000 || test $disk_percentage_usage -ge 80; then
		echo $(echo $line | awk -F: '{print $1}')
	fi
done