#include "matrix.h"


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    // int res = valueExists(matrix, atoi(argv[1]));
    // if(res == 1)printf("encontrei: %d\n ",atoi(argv[1]));
    // else printf("não encontrei: %d\n", atoi(argv[1]));

    linesWithValue(matrix,atoi(argv[1]));

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}