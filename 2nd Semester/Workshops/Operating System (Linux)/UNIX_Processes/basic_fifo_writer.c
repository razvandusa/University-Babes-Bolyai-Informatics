#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
	char* s = "Hello!";
	int f = open("w2r",O_WRONLY);
	int n = strlen(s) + 1;
	write(f,&n,sizeof(int));
	write(f,s,n);
	close(f);
}