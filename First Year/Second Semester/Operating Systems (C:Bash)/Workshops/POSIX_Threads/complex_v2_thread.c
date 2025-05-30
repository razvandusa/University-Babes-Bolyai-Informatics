#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//The last program can be written using a single thread function that gets value to display in the console as argument.

int n = 1;

void* fa(void* arg) {
	for (int i = 0; i < n; i++) {
		printf("%s\n",(char*)arg);
	}
	return NULL;
}

void* fb(void* arg) {
	for (int i = 0; i < n; i++) {
		printf("%s\n",(char*)arg);
	}
	return NULL;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Trebuie sa existe un argument de tip intreg!\n");
		return 0;
	}

	if (atoi(argv[1]) == 0) {
		printf("Argumentul trebuie sa fie de tip intreg!");
		return 0;
	}

	n = atoi(argv[1]);

	pthread_t ta;
	pthread_t tb;
	pthread_create(&ta, NULL, fa, "fa");
	pthread_create(&tb, NULL, fb, "fb");

	for (int i = 0; i < n; i++) {
		printf("main\n");
	}
	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	return 0;
}