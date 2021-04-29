#include <stdio.h>
#include <stdlib.h>
int ** allocationMatrix(int r, int c)
{
    int **x = (int**)calloc(r,sizeof(int*));
    for (int i=0; i<r; i++)
        x[i]=(int*)calloc(c,sizeof(int));
    return x;
}
void deallocationMatrix(int r, int **x)
{
    for (int i=0; i<r; i++)
        free(x[i]);
    free(x);
}
void printMatrix(int n, int m, int **a)
{
    for(int i = 0; i < n; i++)
    {
        printf("\n");
        for(int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
    }
    printf("\n");
}
int minPath(int a, int b, int c)
{
    if(a<=b && a<=c)
        return a;
    if(b<=a && b<=c)
        return b;
    return c;
}
int main(int argc, char const *argv[])
{
    FILE *f = fopen(argv[1], "r");
    int n, m; //a[20][20], b[20][20];
    fscanf(f, "%d%d", &n, &m);
    int **a;
    a = allocationMatrix(n, m);
    int **b;
    b = allocationMatrix(n, m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            fscanf(f, "%d", &a[i][j]);
    printMatrix(n, m, a);
    b[0][0] = a[0][0];
    for(int i = 1; i < n; i++)
        b[i][0] = b[i-1][0] + a[i][0];
    for(int j = 1; j < m; j++)
        b[0][j] = b[0][j-1] + a[0][j];
    for(int i = 1; i < n; i++)
        for(int j = 1; j < m; j++)
        {
            b[i][j] = minPath(b[i-1][j], b[i][j-1], b[i-1][j-1]) + a[i][j];
            //printf("\n%d\n", minPath(b[i-1][j], b[i][j-1], b[i-1][j-1]));
        }
    printMatrix(n, m, b);
    printf("\nThe shortest path is:%d\n", b[n-1][m-1]);
    deallocationMatrix(n, a);
    deallocationMatrix(n, b);
    fclose(f);
    return 0;
}
