#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
//Implement a program that upon receiving SIGINT (Ctrl-C) asks the user if he/she is sure the program should stop, and if
//the answer is yes, stops, otherwise it continues.
void f(int sgn) {
	char option[32];
	printf("Are you sure you want to stop? y/n\n");
	scanf("%s",option);
	if (strcmp(option,"y") == 0) {
		exit(0);
	}
}

int main() {
	signal(SIGINT,f);
	while(1) {}
}