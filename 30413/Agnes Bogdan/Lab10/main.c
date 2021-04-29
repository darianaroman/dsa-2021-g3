#include <stdio.h>
#include <stdlib.h>
int minimum(int a, int b, int c)
{
    int min;
    if(a < b) min = a;
    else min = b;
    if(c < min) min = c;
    return min;
}
int main()
{
    int n, m, i, j, matrix[10][10], aux[10][10];
    printf("number of rows = ");
    scanf("%d", &n);
    printf("number of columns = ");
    scanf("%d", &m);
    /*int *matrix = (int*)malloc(n * m * sizeof(int));
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
        scanf("%d", (matrix + i*m + j));

     for(i = 0; i < n; i++)
        {for(j = 0; j < m; j++)
         printf("%d ", *(matrix + i*m + j));
         printf("\n");}*/

     for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
            scanf("%d", &matrix[i][j]);

     aux[0][0] = matrix[0][0];
     for(i = 1, j = 0; i < n; i++)
        aux[i][j] = aux[i - 1][j] + matrix[i][j];

    for(i = 0, j = 1; j < m; j++)
        aux[i][j] = aux[i][j - 1] + matrix[i][j];

    for(i = 1; i < n; i ++)
        for(j = 1; j < m; j++)
        aux[i][j] = minimum(aux[i - 1][j - 1], aux[i - 1][j], aux[i][j - 1]) + matrix[i][j];
    printf("\nThe auxiliar matrix is:\n");
    for(i = 0; i < n; i++)
        {for(j = 0; j < m; j++)
         printf("%d ", aux[i][j]);
         printf("\n");}
    printf("\nThe minimum path is = %d", aux[n-1][m-1]);
    return 0;
}
