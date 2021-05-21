#include <stdlib.h>
#include <stdio.h>
#define INT_MAX 9999
int min(int a, int b, int c)
{
    if(a>=b && a>=c)
        return a;
    if(b>=a && b>=c)
        return b;
    if(c>=a && c>=b)
        return c;
}
int main()
{int n,m,i,j;

    printf("Number of rows = ");
    scanf("%d",&n);
    printf("\nNumber of columns = ");
    scanf("%d",&m);

    int A[n][m],B[n][m];

    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
        {
            printf("A[%d][%d]= ",i,j);
            scanf("%d", &A[i][j]);
        }
    for(j=0;j<=n;j++)
        B[0][j] = INT_MAX;

    for(i=0;i<=m;i++)
        B[i][0] = INT_MAX;

    for(i=1; i<=n; i++)
        for (j=1; j<=m; j++)
            B[i][j] = A[i][j] + min(B[i-1][j], B[i-1][j-1], B[i][j-1]);

    for(i=1; i<=n; i++)
    {
        for (j=1; j <= m; j++)
            printf("%d ", B[i][j]);
        printf("\n");
    }

    return 0;
}