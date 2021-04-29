#include <stdio.h>
#include <stdlib.h>

int M[3][4] = { {1, 1, 2, 1},
                {1, 5, 3, 6},
                {3, 5, 1, 2}
              };

int minM[3][4];

void printMatrix(int M[3][4], int dim1, int dim2)
{
    int i, j;
    for(i = 0; i < dim1; i++) {
        for(j = 0; j < dim2; j++) {
            printf("%5d", M[i][j]);
        }
        printf("\n");
    }
}

int minT (int a, int b, int c)
{
    if (a > b && a > c) {
        return a;
    }
    if (b > c) {
        return b;
    }
    return c;
}

int minPath (int i, int j)
{
    if (minM[i][j] != 0) {
        return minM[i][j];
    }
    minM[i][j] = M[i][j] + minT(minPath(i-1, j), minPath(i, j-1), minPath(i-1, j-1));
    return minM[i][j];
}


int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    int dim1 = 3;
    int dim2 = 4;

    printMatrix(M, 3, 4);
    printf("\n");
    int i, j;

    int sum = 0;
    for (j = 0; j < dim2; j++) {
        sum = sum + M[0][j];
        minM[0][j] = sum;
    }

    sum = 0;
    for (i = 0; i < dim1; i++) {
        sum = sum + M[i][0];
        minM[i][0] = sum;
    }

    int x = minPath(3, 4);

    printf("%d", minM[3][4]);
    printMatrix(minM, 3, 4);


    return 0;
}
