#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    FILE * f = fopen(argv[1], "r");
    int n, m;
    fscanf(f, "%d %d", &n, &m);
    int **Mat=(int**)malloc(n*sizeof(int*));
    int i, j;
    for(i = 0; i < n; i++) Mat[i]=(int*)malloc(m*sizeof(int));
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++) fscanf(f, "%d", &Mat[i][j]);

    int **Sum=(int**)malloc(n*sizeof(int*));
    for(i = 0; i <= n; i++) Sum[i]=(int*)malloc(m*sizeof(int));
    Sum[0][0]=Mat[0][0];
    for(i = 1; i < n; i++) Sum[i][0] = Sum[i-1][0] + Mat[i][0];
    for(i = 1; i < m; i++) Sum[0][i] = Sum[0][i-1] + Mat[0][i];

    for(i = 1; i < n; i++)
    {
        for(j = 1; j < m; j++)
        {
            Sum[i][j]=Sum[i-1][j]+Mat[i][j];
            int aux;
            aux = Sum[i-1][j-1]+Mat[i][j];
            if(Sum[i][j] > aux) Sum[i][j] = aux;
            aux = Sum[i][j-1]+Mat[i][j];
            if(Sum[i][j] > aux) Sum[i][j] = aux;
        }
    }

    printf("The shortest way to the last cell is of cost: %d", Sum[n-1][m-1]);

    return 0;
}
