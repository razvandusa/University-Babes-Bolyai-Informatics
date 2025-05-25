#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
	int f = open("w2r", O_RDONLY);
	int n;
	read(f, &n, sizeof(int));
	char* s=(char *)malloc(n);
	read(f, s, n);
	close(f);

	printf("%s\n",s);
}