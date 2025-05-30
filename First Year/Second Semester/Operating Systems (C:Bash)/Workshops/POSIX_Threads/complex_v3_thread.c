#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//If we want to pass n as an argument to the thread too (instead of having it a global variable), we need to declare a
//struct since the thread function can only get one argument.
struct arg_t {
	char* name;
	int n;
};

void* f(void* arg) {
	struct arg_t* x = (struct arg_t*)arg;
	for (int i = 0; i < x->n; i++) {
		printf("%s\n", x->name);
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
	struct arg_t a;
	struct arg_t b;
	a.name = "fa"; a.n = atoi(argv[1]);
	b.name = "fb"; b.n = atoi(argv[1]);

	pthread_t ta;
	pthread_t tb;
	pthread_create(&ta, NULL, f, &a);
	pthread_create(&tb, NULL, f, &b);

	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++) {
		printf("main\n");
	}
	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	return 0;
}