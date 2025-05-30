#!/bin/bash

if ! test -x "$1"; then
	echo Primul argument trebuie sa fie executabil!
	exit
fi

clear; ps -f -u vagrant; sleep 5;
./$1 &
while true; do
	clear; ps -f -u vagrant; sleep 1;
done