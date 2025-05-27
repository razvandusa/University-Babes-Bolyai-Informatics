#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//Let's create 10 threads, pass to each of them the order number in which it was created, and have it displayed. The
//program will include a serios bug that causes to a race condition and yields puzzling outputs.

void* f(void* arg) {
    int i = *(int*)arg;
    printf("%d\n", i);
    return NULL;
}

int main() {
    pthread_t t[10];
    for (int i = 0; i < 10; i++) {
        pthread_create(&t[i], NULL, f, &i);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(t[i], NULL);
    }
    return 0;
}