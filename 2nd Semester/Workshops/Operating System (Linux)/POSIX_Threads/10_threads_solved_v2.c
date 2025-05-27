#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//To avoid this situation, we can dynamically allocate an int before creating each thread

void* f(void* arg) {
    int i = *(int*)arg;
    printf("%d\n", i);
    free(arg);
    return NULL;
}

int main() {
    pthread_t t[10];
    for (int i = 0; i < 10; i++) {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        pthread_create(&t[i], NULL, f, p);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(t[i], NULL);
    }
    return 0;
}