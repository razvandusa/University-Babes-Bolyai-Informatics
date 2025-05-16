BEGIN {sum = 0}
{sum += $3}
END {print "The sum of all user id's are : "sum}