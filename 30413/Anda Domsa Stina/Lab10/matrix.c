#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int min(int x, int y, int z)
{
    int min=x;
    if (y < min)
    {
        min=y;
    }
    if(z<min)
    {
        min=z;
    }
	return min;
}

int min_path(int matrix[20][20],int m,int n)
{
    int i, j;
    int aux[m][n];
    aux[0][0]=matrix[0][0]; //first element

    for (i = 1; i <= m; i++) //first column
    {
        aux[i][0] = aux[i-1][0] + matrix[i][0];
    }

    for (j = 1; j <= n; j++) //first row
    {
        aux[0][j]=aux[0][j-1]+matrix[0][j];
    }

    for (i=1; i<=m; i++) //the rest of the matrix
    {
        for(j=1; j<=n; j++)
        {
            aux[i][j]=min(aux[i-1][j],aux[i][j-1],aux[i-1][j-1])+matrix[i][j];
        }
    }
    return aux[m][n];
}
int main()
{
   int m,n,i,j;
   int matrix[20][20];
   scanf("%d %d",&m,&n);
   for(i=0;i<=m;i++)
   {
       printf("Input row %d :",i+1);
       for(j=0;j<=n;j++)
       {
           scanf("%d",&matrix[i][j]);
       }
   }
    int x=min_path(matrix,m,n);
    printf("\n min path:%d",x);
    return 0;
}
