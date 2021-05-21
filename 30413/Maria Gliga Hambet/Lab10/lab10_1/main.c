#include <stdio.h>
#include <stdlib.h>

void alocare(int r, int c, int ***x)
{
    int i;
    *x = (int**)malloc(r*sizeof(int*));
    for (i=0; i<r; i++)
        (*x)[i]=(int*)malloc(c*sizeof(int));
}
void dezalocare(int n, int **x)
{
    int i;
    for (i=0; i<n; i++)
        free(x[i]);
    free(x);
}
void coloana (int **m1, int **m2, int n)
{
    int i;
    for(i=1;i<=n-1;i++)
        m2[i][0]=m2[i-1][0]+m1[i][0];

}
void linie (int **m1, int **m2, int m)
{
    int i;
    for(i=1;i<=m-1;i++)
        m2[0][i]=m2[0][i-1]+m1[0][i];

}
int min3(int a, int b, int c)
{
    if (a<b&&a<c)
        return a;
    if (b<a&&b<c)
        return b;
    return c;
}
void restul (int **m1, int **m2, int n, int m)
{
    int i,j;
    for(i=1;i<=n-1;i++)
        for(j=1;j<=m-1;j++)
    {
        int minim=min3(m2[i-1][j-1],m2[i][j-1],m2[i-1][j]);
        m2[i][j]=minim+m1[i][j];
    }

}

int main()
{
    int n,m,**m1,**m2,i,j;

    printf("Number of lines: n=");
    scanf("%d",&n);
    printf("Number of columns: m=");
    scanf("%d",&m);

    alocare(n,m,&m1);
    alocare(n,m,&m2);

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
        scanf("%d",&m1[i][j]);

    m2[0][0]=m1[0][0];
    coloana(m1,m2,n);
    linie(m1,m2,m);
    restul(m1,m2,n,m);
    printf("\nThe shortest path is %d",m2[n-1][m-1]);
    dezalocare(n,m1);
    dezalocare(n,m2);

    return 0;
}
