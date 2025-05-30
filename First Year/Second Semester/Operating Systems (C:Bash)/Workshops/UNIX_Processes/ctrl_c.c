#include <stdio.h>
#include <signal.h>
//A process can assign a custom function to be executed when a certain signal is received. Let's write a program that
//refuses to stop when it receives Ctrl-C
void f(int sgn) {
	printf("I refuse to stop!\n");
}

int main() {
	signal(SIGINT,f);
	while(1) {}
}