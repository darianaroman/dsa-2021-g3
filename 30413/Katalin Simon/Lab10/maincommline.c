#include <stdio.h>
#include <stdlib.h>

#define maxrow 100
#define maxcol 100
int a[maxrow][maxcol];
int b[maxrow][maxcol]={0};
FILE *input;//="in.txt";
FILE *output;

void printMatrix(int n, int m, int a[][maxcol])
{
     int i, j;
     for(i=0; i<n; i++)
        {
            for(j=0; j<m; j++)
            {
                //printf("%5d",a[i][j]);
                fprintf(output, "%5d",a[i][j]);

            }
            fprintf(output, "\n");
            //printf("\n");
        }
}

int min(int a, int b, int c)
{
    if(a<=b && a<=c) return a;
    if(b<=a && b<=c) return b;
    if(c<=b && c<=a) return c;
}

void calcMin(int n, int m)
{
    int i, j;
    b[0][0]=a[0][0];
    for(i=1; i<n; i++)
    {
        b[i][0]=a[i][0]+b[i-1][0];
    }
    for(i=1; i<m; i++)
    {
        b[0][i]=a[0][i]+b[0][i-1];
    }
    for(i=1; i<n; i++)
    {
        for(j=1; j<m; j++)
        {
            b[i][j]=a[i][j]+min(b[i][j-1], b[i-1][j-1], b[i-1][j]);
        }
    }
}


int main(int argc, char *argv[])
{
    int n,m;
    //input=fopen("in.txt", "r");
    //read from file

    input=fopen(argv[1], "r");
    output=fopen(argv[2], "w");

    fscanf(input,"%d",&n);
    fscanf(input,"%d",&m);

    if(argc==1)
    {
        printf("Please provide the command line arguments");
        return 0;
    }

    //printf("Nr of rows:\n");
    //scanf("%d", &n);
    //printf("Nr of columns:\n");
    //scanf("%d", &m);

    //printf("Please provide the matrix elements:\n");
    int i,j;
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
        {
            //printf("[%d][%d]:=",i, j);
            //scanf("%d", &a[i][j]);
            fscanf(input,"%d",&a[i][j]);

        }


    calcMin(n,m);

    //printf("minimum path length: %d\n",b[n-1][m-1]);
    fprintf("minimum path length: %d\n",b[n-1][m-1]);

    printMatrix(n,m,b);

    return 0;
}
