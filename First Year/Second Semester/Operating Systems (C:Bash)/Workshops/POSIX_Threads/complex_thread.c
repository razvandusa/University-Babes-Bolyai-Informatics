#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int n = 1;

void* fa(void* arg) {
	for (int i = 0; i < n; i++) {
		printf("fa\n");
	}
	return NULL;
}

void* fb(void* arg) {
	for (int i = 0; i < n; i++) {
		printf("fb\n");
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
	pthread_create(&ta, NULL, fa, NULL);
	pthread_create(&tb, NULL, fb, NULL);

	for (int i = 0; i < n; i++) {
		printf("main\n");
	}
	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	return 0;
}