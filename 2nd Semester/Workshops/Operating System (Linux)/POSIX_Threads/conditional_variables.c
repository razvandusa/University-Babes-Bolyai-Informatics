//Here is an example, where a car needs 40 units of fuel to start. Another thread fills the fuel tank
//in parts, and the car thread waits until there is enough fuel.
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t m;
pthread_cond_t cond;
int fuel;

void* fuel_filling(void * arg) {
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&m);
        fuel += 15;
        printf("Filled fuel.. %d\n",fuel);
        pthread_mutex_unlock(&m);
        pthread_cond_signal(&cond);
        sleep(1);
    }
    return NULL;
}

void* car(void* arg) {
    pthread_mutex_lock(&m);
    while (fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&cond,&m);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&m);
    return NULL;
}

int main() {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t car_t;
    pthread_create(&car_t, NULL, car, NULL);

    pthread_t fuel_t;
    pthread_create(&fuel_t, NULL, fuel_filling, NULL);

    pthread_join(car_t, NULL);
    pthread_join(fuel_t, NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cond);
    return 0;
}