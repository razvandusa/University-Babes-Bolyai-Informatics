#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* f(void* arg) {
	printf("Thread/Hello World!\n");
	return NULL;
}

int main() {
	pthread_t t;
	pthread_create(&t,NULL,f,NULL);
	printf("Main/Hello World!\n");
	pthread_join(t,NULL);
}