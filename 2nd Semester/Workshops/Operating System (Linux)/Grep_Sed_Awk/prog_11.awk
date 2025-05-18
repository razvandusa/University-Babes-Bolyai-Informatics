BEGIN {
	PIDs=0
	count=0
}
$2~/^[0-9]*$/{
	PIDs+=$2
	count+=1
}
END {
	print PIDs/count
}