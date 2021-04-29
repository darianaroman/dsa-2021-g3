#include <stdio.h>
#include <stdlib.h>


int minde2(int x, int y)
{ return (x < y) ? x : y; }


int minde3(int x, int y, int z)
{ return minde2(minde2(x, y), z); }

int a[20][20];

int costminim(int a[][20], int n, int m)
{
	int drum[20][20];
    drum[0][0]=a[0][0];

    int i;
	for (i=1; i<=n; i++){
    drum[i][0] = drum[i-1][0]+a[i][0];
	}



    int j;
	for (j=1; j<=m; j++){
    drum[0][j]=drum[0][j-1]+a[0][j];
    }

	for (i=1; i<=n; i++){
        for (j=1; j<=m; j++){
            drum[i][j] = a[i][j] + minde3(drum[i-1][j], drum[i-1][j-1], drum[i][j-1]);
        }
	}
	return drum[n][m];
}



int main()
{
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    int i, j;
    for (i=0; i<=n; i++)
        for (j=0; j<=m; j++)
    scanf("%d", &a[i][j]);

    printf("%d", costminim(a, n, m));
    return 0;
}
