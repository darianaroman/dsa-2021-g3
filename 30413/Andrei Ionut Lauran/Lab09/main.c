#include <stdio.h>
#include <stdlib.h>

int maximum(int x, int y, int z)
{
    if (x > y && x > z)
        return x;
    else
        if (y > x && y > z)
            return y;
        else
        return z;
}

int maxCrossingSum(int *v, int n, int m, int h)
{
    int sum = 0;
    int LSum = -2000000, RSum = -2000000;
    for (int i = m; i >= n; i--)
    {
        sum = sum + v[i];
        if (sum > LSum)
            LSum = sum;
    }
    sum = 0;
    for (int i = m + 1; i <= h; i++)
    {
        sum = sum + v[i];
        if (sum > RSum)
            RSum = sum;
    }
    return LSum + RSum;
}

int contigSum(int v[], int n, int h)
{
    if (n == h)
        return v[n];
    int m = (n + h)/2;
    return maximum(contigSum(v, n, m), contigSum(v, m+1, h), maxCrossingSum(v, n, m, h));
}

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1],"r");
    FILE *g = fopen(argv[2],"w");
    int n;
    if(f == NULL)
    {
        printf("Error:input file not found");
        exit(1);
    }
    fscanf(f,"%d",&n);
    int v[n];
    for(int i=0; i<n; i++)
        fscanf(f,"%d",&v[i]);
    fprintf(g,"The maximum contiguous sum is:%d\n", contigSum(v,0,n-1));
    return 0;
}
