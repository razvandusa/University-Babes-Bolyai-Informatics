{
	ora = substr($7,1,1) * 10;
	ora += substr($7,2,1);
	if (ora >= 23) {
		print $1
	}
}