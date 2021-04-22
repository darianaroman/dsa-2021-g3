#include <stdio.h>
#include <stdlib.h>
/// open a file (if possible)
FILE *openCheck (const char *path, const char *mode)
{
    FILE *pf = fopen(path,mode);
    if (pf == NULL)
    {
        puts("cannot open the file");
        exit(1);
    }
    return pf;
}
int getDimension (FILE *pIn)
{
    int n, x, y, max = 0;
    fscanf(pIn,"%d",&n);
    for (int i = 1; i <= n; i++)
    {
        fscanf(pIn,"%d%d",&x,&y);
        if (x > max) max = x;
        if (y > max) max = y;
    }
    rewind(pIn);
    return max;
}
void initializeMatrix (int dim, int mat[dim][dim])
{
    for (int i = 1; i <= dim; i++)
        for (int j = 1; j <= dim; j++)
            mat[i][j] = 0;
}
void adjacencyMatrix (int nr_rel, int dim, int mat[dim][dim], FILE *pIn)
{
    int x, y;
    for (int i = 1; i <= nr_rel; i++)
    {
        fscanf(pIn,"%d%d",&x,&y);
        mat[x][y] = 1;
    }
}
void printMatrix (int dim, int mat[dim][dim])
{
    for (int i = 1; i <= dim; i++)
    {
        for (int j = 1; j <= dim; j++)
            printf("%d ",mat[i][j]);
        putchar('\n');
    }
    putchar('\n');
}
void initializeVector (int dim, int v[dim])
{
    for (int i = 1; i <= dim; i++)
        v[i] = 0;
}
void addRows (int dim, int deg[dim], int mat[dim][dim])
{
    for (int i = 1; i <= dim; i++)
        for (int j = 1; j <= dim; j++)
            deg[i] += mat[j][i];
}
int main(int argc, char *argv[])
{
    FILE *pIn = openCheck(argv[1], "r");
    FILE *pOut = openCheck(argv[2], "w");
    int dim = getDimension(pIn);
    int mat[dim][dim];
    initializeMatrix(dim,mat);
    //printMatrix(dim,mat);
    int nr_rel;
    fscanf(pIn,"%d",&nr_rel);
    adjacencyMatrix(nr_rel,dim,mat,pIn);
    //printMatrix(dim,mat);
    int deg[dim];
    initializeVector(dim,deg);
    /*for (int i = 1; i <= dim; i++)
        printf("%d ",deg[i]);*/
    addRows(dim,deg,mat);
    /*for (int i = 1; i <= dim; i++)
        printf("%d ",deg[i]);*/
    int cnt = nr_rel;
    while(cnt != 0)
    {
        for (int i = 1; i <= dim; i++)
        {
            if(deg[i]==0)
            {
                for (int j = 1; j <= dim; j++)
                    if (mat[i][j]) deg[j]--;
                deg[i]--;
            }
            if (deg[i] == -1)
            {
                fprintf(pOut,"%d ",i);
                deg[i] = -2;
            }
        }
        cnt--;
    }
    fclose(pIn);
    fclose(pOut);
    return 0;
}
