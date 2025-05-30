#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int pid = fork();
	if (pid == 0) {
		printf("Hello World!\n");
		exit(0);
	}
	wait(0);
	printf("Hello World!\n");
}