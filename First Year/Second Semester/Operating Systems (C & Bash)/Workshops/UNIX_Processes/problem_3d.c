#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void f(int n) {
	if (n > 0) {
		int pid = fork();
		if (pid == 0) {
			printf("Hello World!\n");
			f(n-1);
			exit(0);
		}
		wait(0);
	}
}

int main() {
	f(3);
}