//Write a program that gets programs as command line arguments, and executes them using fork and exec.
// In case exec fails or the program it executes exits with an error code, report the relevant details standard error.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int status;
	for (int i = 1; i < argc; i++) {
		if (fork() == 0) {
			if (execlp(argv[i], argv[i], NULL) == -1) {
				fprintf(stderr,"Failed to launch %s : %s",argv[i],strerror(errno));
				printf("\n");
			}
			exit(0);
		}
		wait(&status);
	}
}