#include <stdio.h>
#include <stdlib.h>

void greeting(char *name) {
    printf("Hello %s", name);
}
int main() {
    char *name = NULL;
    size_t lungime;
    printf("Type your name : ");
    while(getline(&name, &lungime, stdin) != -1) {
        greeting(name);
        printf("Type your name : ");
    }
}