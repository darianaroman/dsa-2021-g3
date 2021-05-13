#include <stdio.h>
#include <stdlib.h>

int mat[50][50], DP[50][50], n, m;

int min3(int a, int b, int c) ///utility function
{
    if( a<=b )
        if( a<=c ) return a;
           else return c;
        else if(b<=c) return b;
}

int LowCostMatrix()
{
    int min,i,j,DP[50][50];
    DP[1][1]= mat[1][1];
    for(i=1;i<=m;i++)
        DP[1][j]= mat[1][j] + DP[1][j-1];
    for(i=1;i<=n;i++)
        DP[i][1]= mat[i][1] + DP[i-1][1];
    for(i=2;i<=n;i++)
        for(j=2;j<=m;j++)
            DP[i][j]= mat[i][j]+ min3( DP[i-1][j], DP[i-1][j-1], DP[i][j-1]);

    return DP[n][m];
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&mat[i][j]);

    int dp=LowCostMatrix(); ///generate the full lowest cost path matrix

    printf("\nThe lowest costing path is %d", dp);

}
