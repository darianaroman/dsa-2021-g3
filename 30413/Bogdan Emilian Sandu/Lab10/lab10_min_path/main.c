#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){
    if(a <= b) return a;
    else return b;
}

int min3nr(int a, int b, int c){
    return min(min(a,b),c);
}

int minPath(int **m,int row, int col)
{
    int mCost[row][col];
    mCost[0][0] = m[0][0];
    for(int i = 1; i < col; i++)
        mCost[0][i] = mCost[0][i-1] + m[0][i];
    for(int i = 1; i < row; i++)
        mCost[i][0] = mCost[i-1][0] + m[i][0];
    for(int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            mCost[i][j] = min3nr(mCost[i - 1][j], mCost[i][j - 1], mCost[i - 1][j - 1]) + m[i][j];
        }
    }
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ",mCost[i][j]);
        }
        printf("\n");
    }
    return mCost[row-1][col-1];
}



int main() {
    int row,col;
    printf("Introdu nr randuri si nr coloane\n");
    scanf("%d %d",&row,&col);
    int **m = (int **)malloc(row*sizeof(int*));
    for(int i = 0; i < col; i++)
        m[i] = (int *)malloc(col*sizeof(int));
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("Introdu elementul de pe pozitia %d,%d\n", i, j);
            scanf("%d", &m[i][j]);
        }
    }
    printf("Minimum cost of path is: %d", minPath(m,row,col));



    return 0;
}
