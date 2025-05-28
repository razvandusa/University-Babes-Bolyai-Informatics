//Write a C program that receives a filename and a number N as command-line
//arguments. The main process opens the file and then creates N threads. Each thread
//will read one line at a time from the file and will update some variables that hold the total
//number of lines, words, and characters for the entire file processed so far.
//Once all the threads terminate, the main process prints the total number of lines, words,
//and characters from the given file. (The output should be equivalent to wc -lwc file).
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
pthread_mutex_t m;
int l, w, c;

void* routine(void* arg) {
	char line[1000];
	pthread_mutex_lock(&m);
	if (fgets(line, sizeof(line), (FILE*)arg) == NULL) {
		pthread_mutex_unlock(&m);
                return NULL;
        }
	l += 1;
	int i = 0;
	while (line[i] != '\0') {
		c++;
		if (line[i] == ' ' || line[i] == '\n') {
			w++;
		}
		i++;
	}
	pthread_mutex_unlock(&m);

	return NULL;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("The program needs two arguments, a flename and a number N\n");
		exit(0);
	}

	if (atoi(argv[2]) == 0) {
		printf("Second argument needs to be a number!\n");
		exit(0);
	}

	FILE* f = fopen(argv[1], "r");

	if (f == NULL) {
		printf("Could not open the file!\n");
		exit(0);
	}

	int n = atoi(argv[2]);
	pthread_t t[n];
	pthread_mutex_init(&m, NULL);

	for (int i = 0; i < n; i++) {
		pthread_create(&t[i], NULL, routine, f);
	}

	for (int i = 0; i < n; i++) {
		pthread_join(t[i], NULL);
	}

	printf("%d %d %d %s\n", l, w, c, argv[1]);

	pthread_mutex_destroy(&m);
	return 0;
}