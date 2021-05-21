#include <stdio.h>
#include <stdlib.h>

int mat[100][100];
int sum[100][100];

int min (int a, int b, int c)
{
    if(a <= b && a <= c)
        return a;
    if(b <= a && b <= c)
        return b;
    if(c <= a && c <= b)
        return c;
    else return a;
}

int main()
{

    /// dynamic programming

    int n, m;

    FILE *f = fopen("mat.txt", "r");
    fscanf(f, "%d%d", &n, &m);
    for(int i = 1; i<= n; i++)
        for(int j =1; j<=m; j++)
            fscanf(f, "%d", &mat[i][j]);


    for(int j = 1; j<= n; j++)
        sum[0][j] = 100000;
    for (int i = 1; i<=m; i++)
        sum[i][0] = 100000;
    for(int i = 1; i<= n; i++)

        for(int j =1; j<=m; j++)
        {

            sum[i][j] = min(sum[i][j-1],sum[i-1][j-1],sum[i-1][j]) + mat[i][j];
        }
    /*
    for(int i = 1; i<= n; i++){
        for(int j =1; j<=m; j++)
            printf("%d ", sum[i][j]);
        printf("\n");
    }

    */

    ///costu minim in ultimu nod :
    printf("costul minim din mat[0][0] la mat[n][m] este %d", sum[n][m]);
    return 0;

}
//printf("%d %d %d %d", min(1,2,3),min(1,3,3),min(3,3,3),min(2,1,-2));
