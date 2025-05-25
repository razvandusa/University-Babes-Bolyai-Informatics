#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	for (int i = 1; i <= 6; i++) {
		if (i % 2 == 0 && fork() == 0) {
			printf("Hello World\n");
			exit(0);
		}
		wait(0);
	}
}