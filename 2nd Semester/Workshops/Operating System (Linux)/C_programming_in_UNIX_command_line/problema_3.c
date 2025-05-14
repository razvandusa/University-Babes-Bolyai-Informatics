/*
 *Consider a text file storing a matrix as follows: the numbers of rows and columns are on the first line separated
 *by space, and on the subsequent lines, are the elements of the matrix separated by space. Here is file m.txt
 *
 *Read a matrix of integers from a text file and display to it in the console.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("For the program to run please provide 2 arguments!\n");
        return 0;
    }
z
    FILE* f = fopen(argv[1],"r");
    int n, m;
    fscanf(f, "%d %d", &n, &m);

    int** matrice = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrice[i] = (int*)malloc(m * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(f, "%d", &matrice[i][j]);
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
    
    fclose(f);
    for (int i = 0; i < n; i++) {
        free(matrice[i]);
    }
    free(matrice);

}
