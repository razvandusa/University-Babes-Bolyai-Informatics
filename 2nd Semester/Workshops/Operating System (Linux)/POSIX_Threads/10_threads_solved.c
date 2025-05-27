#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//To avoid this situation, we can have an array of ints and send each thread the address of another
//element

void* f(void* arg) {
    int i = *(int*)arg;
    printf("%d\n", i);
    return NULL;
}

int main() {
    pthread_t t[10];
    int a[10];
    for (int i = 0; i < 10; i++) {
        a[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        pthread_create(&t[i], NULL, f, &a[i]);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(t[i], NULL);
    }
    return 0;
}
