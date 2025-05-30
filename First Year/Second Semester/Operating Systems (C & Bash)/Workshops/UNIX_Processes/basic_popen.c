//Write a program that generates the "99 bottles of beer" song, and displays it in a pager like less.
#include <stdio.h>

int main() {
	FILE* fd = popen("less","w");
	for (int i = 99; i >= 0; i--) {
		fprintf(fd, "%d bottles of beer on the wall,\n", i);
		fprintf(fd, " %d bottles of beer.\n", i);
		fprintf(fd, "If one of those bottles should happen to fall,\n");
		fprintf(fd, " %d bottles of beer on the wall.\n\n", i-1);
	}
	pclose(fd);
	return 0;
}