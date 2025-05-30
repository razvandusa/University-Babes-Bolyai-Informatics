//Here is an example simulating the purchasing product X of which there is an initial stock of 10 pieces. Most shoppers
//just check the availability of the product, and only some of them buy it.
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int x = 10;
pthread_rwlock_t rwl;

void* shop(void* arg) {
    int id = *(int*)arg;
    if (id % 10 == 0) {
        pthread_rwlock_wrlock(&rwl);
        if (x > 0) {
            printf("Item %d has just been bought by %d!\n", x, id);
            x--;
        } else {
            printf("There are no more items in stock, we're sorry %d!\n", id);
        }
        pthread_rwlock_unlock(&rwl);
    } else {
        pthread_rwlock_rdlock(&rwl);
        printf("%d, there are %d more item to be bought\n", id, x);
        pthread_rwlock_unlock(&rwl);
    }
    free(arg);
    return NULL;
}

int main() {
    pthread_t t[200];
    pthread_rwlock_init(&rwl, NULL);

    for (int i = 0; i < 200; i++) {
        int* p = (int *)malloc(sizeof(int));
        *p = i;
        pthread_create(&t[i], NULL, shop, p);
    }

    for (int i = 0; i < 200; i++) {
        pthread_join(t[i], NULL);
    }

    pthread_rwlock_destroy(&rwl);
    return 0;
}