BEGIN {
        m = 0
        w = 0
}
$5 ~ /.* .*a\>/ {
        w++
}
$5 ~ /.* .*[a-z]\>/ {
        m++
}
END {
        print "Men : "m
        print "Women : "w
}