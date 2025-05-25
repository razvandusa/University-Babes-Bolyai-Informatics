#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

//Write a program that creates three child processes that just loop forever. When the parent process gets SIGUSR1 it
//sends SIGUSR2 to the child processes. When the parent process gets SIGUSR2, it sends SIGKILL to the child processes.
//The child processes should report the signals received. Note in the solution below that the child process does not
//override the SIGKILL handler, as it will not have any effect.
int children[3];

void handler_parent(int sgn) {
	if (sgn == SIGUSR1) {
		printf("Parent sending SIGUSR2\n");
		for (int i = 0; i < 3; i++) {
			kill(children[i], SIGUSR2);
		}
	} else if (sgn == SIGUSR2) {
		printf("Parent sending SIGKILL to the child processes\n");
		for (int i = 0; i < 3; i++) {
			kill(children[i], SIGKILL);
		}
	}
}

void handler_child(int sgn) {
	if (sgn == SIGUSR2) {
		printf("Child %d recieves signal SIGUSR2\n", getpid());
	}
}

int main() {
	signal(SIGUSR1, handler_parent);
	signal(SIGUSR2, handler_parent);
	for (int i = 0; i < 3; i++) {
		children[i] = fork();
		if (children[i] == 0) {
			signal(SIGUSR2, handler_child);
			while(1) {}
			exit(0);
		}
	}
	wait(0); wait(0); wait(0);
}