#include <stdio.h>
#include <stdlib.h>
int min2(int a, int b)
{
    return (a < b) ? a : b;
}

int min3(int a, int b, int c)
{
    return min2(min2(a, b), c);
}
int ** alocare(int r, int c)
{
    int **x = (int**)malloc(r*sizeof(int*));
    for (int i=0; i<r; i++)
        x[i]=(int*)malloc(c*sizeof(int));
    return x;
}
void dezalocare(int r, int **x)
{
    for (int i=0; i<r; i++)
        free(x[i]); // dezaloca fiecare linie
    free(x); // dezaloca sirul de pointeri la linii
}

void costMatrix(int **v, int **c,int n,int m)
{
    int i,j;
    //int c[100][100];
    c[0][0]=v[0][0];
    for(i=1; i<m; i++)
    {
        c[0][i]=v[0][i]+c[0][i-1];

    }
    for(i=1; i<n; i++)
    {
        c[i][0]=v[i][0]+c[i-1][0];
    }

    for(i=1; i<n; i++)
        for(j=1; j<m; j++)
        {
            c[i][j]=v[i][j]+min3(c[i-1][j],c[i][j-1],c[i-1][j-1]);
        }



}
int main()
{
    int **V,**cost;
    int n,m;

    printf("Number of lines: ");
    scanf("%d",&n);
    printf("\nNumber of columns: ");
    scanf("%d",&m);

    V=alocare(n,m);
    cost=alocare(n,m);

    printf("\nThe matrix is:\n");
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            scanf("%d",&V[i][j]);

    costMatrix(V,cost,n,m);

    /* for(int i=0;i<n;i++)
      {
          for(int j=0;j<m;j++)
              printf("%d ",cost[i][j]);
          printf("\n");
      }*/

    printf("Minimum cost of the matrix is: %d",cost[n-1][m-1]);
    dezalocare(n,V);
    dezalocare(n,cost);

    return 0;
}
