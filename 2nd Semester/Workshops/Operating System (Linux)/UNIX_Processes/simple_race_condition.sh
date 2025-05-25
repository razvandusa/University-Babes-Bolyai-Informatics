#!/bin/bash

arg=$1
V=0
while test $V -lt 2000; do
	N=$(cat $arg) #citeste valoarea din fisier
	N=$(($N + 1)) #o incrementeaza
	echo $N > $arg #scrie valoarea nou in fisier
	V=$(($V + 1))
done