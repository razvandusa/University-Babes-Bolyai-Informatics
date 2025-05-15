//Store the matrix in a binary file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void freeMemory(int** matrice, int row) {
    for (int i = 0; i < row; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

int main(int argc,char** argv) {
    if (argc != 3) {
        printf("Please provide 3 arguments!");
        return 0;
    }

    FILE* fr = fopen(argv[1],"r");
    FILE* fw = fopen(argv[2],"w");

    int row, cols;
    fscanf(fr,"%d",&row);
    fscanf(fr,"%d",&cols);

    int** matrice = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++) {
        matrice[i] = (int*)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(fr,"%d",&matrice[i][j]);
            fprintf(fw,"%d ",matrice[i][j]);
        }
        fprintf(fw,"\n");
    }

    freeMemory(matrice,row);
    fclose(fr);
    fclose(fw);
}