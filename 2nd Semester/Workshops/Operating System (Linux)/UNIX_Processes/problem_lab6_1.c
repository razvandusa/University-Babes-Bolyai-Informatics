#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	for (int i = 0; i < 3; i++) {
		if (fork() == 0) {
			printf("Hello world!\n");
			for (int i = 0; i < 3; i++) {
				if (fork() == 0) {
					printf("Hello world!\n");
					exit(0);
				}
				wait(0);
			}
			exit(0);
		}
		wait(0);
	}
}