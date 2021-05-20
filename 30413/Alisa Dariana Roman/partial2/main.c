#include <stdio.h>
#include <stdlib.h>

//int nrPaths(int n, int m)
//{
//    if (n <= 1 && m <= 1) {
//        return 0;
//    }
//    return nrPaths(n-1, m-1) + nrPaths(n-1, m) + nrPaths(n, m-1);
//}

int main()
{
    int n, m;
    n = 3;
    m = 3;
    int max[n][m];
    int i, j;


    for (i = 0; i < n; i ++) {
        max[0][i] = i;
    }

    for (j = 0; j < m; j ++) {
        max[j][0] = j;
    }

    for ( i = 1 ; i < n; i ++) {
        for ( j=1; j<m; j++) {
            max[i][j] = max[i-1][j-1] + max[i][j-1] + max[j-1][i];
        }
    }



    printf ("%d\n", max[n-1][m-1]);

    return 0;
}
