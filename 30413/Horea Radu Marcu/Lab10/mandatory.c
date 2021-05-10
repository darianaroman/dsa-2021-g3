#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int verificare(int n, int *nr, int dif, int *v)
{
    int **Mat = (int**)malloc(n*sizeof(int*));
    int i, j;
    int a = *nr;
    for(i = 0; i < n; i++) Mat[i] = (int*)malloc(n*sizeof(int));
    for(i = 0; i < n; i++)
    {
        Mat[i][0] = v[i];
        if(v[i] == dif)
        {
        a ++;
        return a;
        }
    }
    a ++;
    for(i = 0; i < n; i++)
    {
        for(j = 1; j < n; j++)
        {
            Mat[i][j] = Mat[i][0] + Mat[j][0];
            if(Mat[i][j] == dif)
            {
            a ++;
            return a;
            }
        }
    }
    for(i = 0; i < n; i++)
    {
        for(j = 1; j < n; j++)
        {
            Mat[i][j] = Mat[i][0] - Mat[j][0];
            if(Mat[i][j] == dif)
            {
            a ++;
            return a;
            }
        }
    }
    *nr = *nr + 1;
    return 0;
}
int main(int argc,char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    int A, B;
    int n = 0;
    int v[102], x;
    fscanf(f, "%d %d", &A, &B);
    while(fscanf(f,"%d", &x) == 1) v[n++] = x;

    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(v[i]<v[j])
            {
                int aux;
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    int nr = 0;
    int dif = A - B;
    if (dif < 0) dif = - dif;
    int ok = verificare(n, &nr, dif, v);
    if(ok)
    {
        printf("%d", ok);
        return 0;
    }
    while(!ok)
    {
        int *v1 = (int*)malloc(n*n*sizeof(int));
        n = n * n;
        i = 0;
        int k;
        while(i < n)
        {
            for(j = 0; j < sqrt(n); j++)
            {
                for(k = 0; k < sqrt(n); k++) v1[i++]=v[j]+v[k];
            }
        }
        ok = verificare(n, &nr, dif, v1);
        if(!ok)
        {
          while(i < n)
            {
            for(j = 0; j < sqrt(n); j++)
            {
                for(k = 0; k < sqrt(n); k++) v1[i++]=v[j]-v[k];
            }
        }
        }
    }
    printf("%d", ok);
    return 0;
}
