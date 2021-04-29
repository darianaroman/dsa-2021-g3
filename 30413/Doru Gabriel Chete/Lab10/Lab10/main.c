#include <stdio.h>
#include <stdlib.h>

int matrix1[100][100];
int matrix2[100][100];

int min(int x, int y, int z)
{
    if(x<y && x<z)
    {
        return x;
    }
    else if(y<z) //compare num2 and num1
    {
        return y;
    }
    else
    {
        return z;
    }




}
int main()
{
    int n, m;
    printf("Specify matrix dimensions: N = ");
    scanf("%d", &n);
    printf("\nWrite matrix elements: ");
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            scanf("%d", &matrix1[i][j]);
        }
    }

    matrix2[1][1] = matrix1[1][1];
    for(int j = 2; j <= n; j++)
    {
        matrix2[1][j] = matrix1[1][j] + matrix2[1][j-1];
        matrix2[j][1] = matrix1[j][1] + matrix2[j-1][1];
    }



    for(int i = 2; i <= n - 1; i++)
    {
        matrix2[i][i] = min(matrix2[i-1][i], matrix2[i-1][i-1], matrix2[i][i-1]) + matrix1[i][i];
        for(int j = i + 1; j <= n; j++)
        {
            matrix2[i][j] = min(matrix2[i-1][j], matrix2[i-1][j-1], matrix2[i][j-1]) + matrix1[i][j];
        }
        for(int j = 2; j <= i; j++)
        {
            matrix2[i+1][j] = min(matrix2[i][j], matrix2[i][j-1], matrix2[i+1][j-1]) + matrix1[i+1][j];
        }
    }

    //final computation
    matrix2[n][n] = min(matrix2[n-1][n], matrix2[n-1][n-1], matrix2[n][n-1]) + matrix1[n][n];


                    printf("The 2nd matrix is:\n");
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
}
