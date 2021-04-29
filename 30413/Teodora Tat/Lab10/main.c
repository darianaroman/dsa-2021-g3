#include <stdio.h>
#include <stdlib.h>
int minimum(int a,int b,int c){
    if(a<=b && a<=c)
        return a;
    else if(b<=a && b<=c)
        return b;
    else
        return c;
}
void minPath(int a[4][7],int n,int m){
    int b[10][10],i,j;
    for (i=0; i<n; i++)
        for(j=0; j<m; j++)
            b[i][j]=0;
    b[0][0]=a[0][0];
    for(j=1; j<m; j++)
        b[0][j]=a[0][j]+b[0][j-1];
    for(i=1; i<n; i++)
        b[i][0]=a[i][0]+b[i-1][0];
    for (i=1; i<n; i++)
        for(j=1; j<m; j++)
        {
            b[i][j]=minimum(b[i-1][j-1],b[i-1][j],b[i][j-1])+a[i][j];
        }
    printf("%d", b[n-1][m-1]);

}
int main()
{
    int a[4][7],m,n,i,j;
    scanf("%d %d",&n,&m);
    for (i=0; i<n; i++)
        for(j=0; j<m; j++)
            scanf("%d",&a[i][j]);
    minPath(a, n,m);
    return 0;
}
