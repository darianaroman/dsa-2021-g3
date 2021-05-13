#include <stdio.h>
#include <stdlib.h>

#define max_limit 100

int mat[max_limit][max_limit];
int min_path_mat[max_limit][max_limit];

int min2(int x, int y){
    if (x<y)
        return x;
    return y;
}

int min(int x, int y, int z){
    return min2(min2(x, y), z);
}

int min_path(int n, int m){
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j){
            min_path_mat[i][j]=mat[i][j];
            if (i>1 && j>1)
                min_path_mat[i][j]+=min(min_path_mat[i][j-1], min_path_mat[i-1][j], min_path_mat[i-1][j-1]);
            else if(i==1 && j>1)
                min_path_mat[i][j]+=min_path_mat[i][j-1];
            else if(i>1 && j==1)
                min_path_mat[i][j]+=mat[i-1][j];
            }
    return min_path_mat[n][m];
}

int main()
{
    FILE *in=fopen("./in.txt", "r");
    FILE *out=fopen("./out.txt", "w");

    int n, m;
    fscanf(in, "%d %d", &n, &m);
    for (int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            fscanf(in, "%d", &mat[i][j]);

    int l=min_path(n, m);

    for (int i=1;i<=n;++i){                 //print the generated matrix
        for(int j=1;j<=m;++j)
            printf("%d ", min_path_mat[i][j]);
        printf("\n");
        }
    printf("\nmin path between mat[1][1] and mat[n][m] is %d\n", l);

    return 0;
}
