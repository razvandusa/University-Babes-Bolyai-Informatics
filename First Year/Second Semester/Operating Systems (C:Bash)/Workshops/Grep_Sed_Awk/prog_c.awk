BEGIN {prod = 1}
{
	prod *= $3-$4
}
END {print "The product of the multiplication of all the differences between the user id and the group id : "prod}