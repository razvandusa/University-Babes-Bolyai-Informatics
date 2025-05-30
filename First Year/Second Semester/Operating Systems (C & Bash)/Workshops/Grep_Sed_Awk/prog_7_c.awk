{
	minute = 0
	ore = 0
	for (i = 1; i < length($10); i++) {
		if (i == 2 || i == 3) {
			ore += substr($10,i,1)
		}
		if (i == 5) {
			minute += 10 * substr($10,i,1)
		}
		if (i == 6) {
			minute += substr($10,i,1)
		}
	}
	minute = minute + 60 * ore
	arr[$1] += minute
}
END {
	for (user in arr) {
		print user " " arr[user]
	}
}