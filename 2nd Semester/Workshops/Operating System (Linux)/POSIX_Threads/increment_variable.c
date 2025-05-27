//Let's write a program that creates 10 threads, each of which increments a global variable as many times given as a
//command line argument.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int val;

void* f(void* arg) {
    int n = *(int *)arg;
    for (int i = 0; i < n; i++) {
        val = val + 1;
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
    for (int i = 0; i < 10; i++) {
        pthread_create(&t[i], NULL, f, &n);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(t[i], NULL);
    }

    printf("%d\n", val);
}