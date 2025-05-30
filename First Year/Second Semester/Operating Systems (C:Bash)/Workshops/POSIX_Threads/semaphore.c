//Here is an example that simulates a car wash station that has only 4 washing slots for cars. We have 10 cars (threads) and each one of them needs to wait for a free spot.
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
sem_t semaphore;

void* car_wash(void* arg) {
    sem_wait(&semaphore);
    printf("Car %d is being washed now...\n", *(int *)arg);
    int n = random() % 10;
    sleep(n);
    printf("Car %d is done being washed!\n", *(int*) arg);
    sem_post(&semaphore);

    free(arg);
    return NULL;
}

int main() {
    sem_init(&semaphore, 0, 4);
    pthread_t t[10];
    for (int i = 0; i < 10; i++) {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        pthread_create(&t[i], NULL, car_wash, p);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(t[i], NULL);
    }
    sem_destroy(&semaphore);

    return 0;
}