//Here is an example where 10 threads work in phases. All mush finish phase 1 before phase 2 begins.
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
pthread_barrier_t barrier;

void* routine(void* arg) {
    while (1) {
        int n = random() % 10;
        sleep(n);
        //finished phase 1
        printf("Worker %d waiting at the barrier...\n",*(int *)arg);
        pthread_barrier_wait(&barrier);
        printf("Worker %d passed the barrier\n", *(int *)arg);
        sleep(n);
        //finished phase 2
    }
}

int main() {
    pthread_t t[10];
    pthread_barrier_init(&barrier, NULL, 10);

    for (int i = 0; i < 10; i++) {
        int* p = (int*)malloc(sizeof(int));
        *p = i;
        pthread_create(&t[i], NULL, routine, p);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(t[i], NULL);
    }
    pthread_barrier_destroy(&barrier);

    return 0;
}