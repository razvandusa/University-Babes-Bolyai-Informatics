//The race condition can be avoided using a mutex as shown below
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int val;
pthread_mutex_t m;

void* f(void* arg) {
    int n = *(int *)arg;
    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&m);
        val = val + 1;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Program needs to have one argument!\n");
        return 0;
    }
    if (atoi(argv[1]) == 0) {
        printf("The argument needs to be an integer!\n");
        return 0;
    }

    int n = atoi(argv[1]);
    pthread_t t[10];
    pthread_mutex_init(&m, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_create(&t[i], NULL, f, &n);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(t[i], NULL);
    }

    pthread_mutex_destroy(&m);
    printf("%d\n", val);
}