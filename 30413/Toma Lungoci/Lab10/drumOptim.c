#include <stdio.h>
#include <stdlib.h>
#define R 3
#define C 4
int min2(int a, int b) { return (a < b) ? a : b; }
int min3(int a, int b, int c) { return min2(min2(a, b), c); }
int costMatrix[R][C]={0};
void buildCostMatrix(int matrix[R][C])
{
    int row=0, col=0;
    costMatrix[row][col]=matrix[row][col];
    for(col=0, row=1; row<R; row++)
    {
        costMatrix[row][col]=costMatrix[row-1][col]+ matrix[row][col];
    }

    for(col=1, row=0; col<C; col++)
    {
        costMatrix[row][col]=costMatrix[row][col-1]+ matrix[row][col];
    }
    //completed the first row and column of the costMatrix
    for(col=1; col<C; col++)
    {
        for(row=1; row<R; row++)
        {
            costMatrix[row][col]=min3(costMatrix[row][col-1], costMatrix[row-1][col], costMatrix[row-1][col-1]) +matrix[row][col];//all the 3 possible ways to go

        }
    }
}

int main()
{
    int matrix[R][C] = {1, 3, 5, 2, 4, 0, 1, 3, 1, 2, 2, 4};
    buildCostMatrix(matrix);
    for(int i=0; i<R; i++)
    {
        for(int j=0; j<C; j++)
        {
            printf("%d ", costMatrix[i][j]);//printing the whole matrix because, similar to the shortest path greedy alg, it shows the optimal path at every step.
        }
        printf("\n");
    }
    return 0;
}
