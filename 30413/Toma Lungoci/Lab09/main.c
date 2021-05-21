#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int max2(int a, int b) { return (a > b) ? a : b; }
int max3(int a, int b, int c) { return max2(max2(a, b), c); }

int maxCrossingSum(int array[], int l, int m, int r)
{
    int sum=0;
    int left_sum=INT_MIN;
    for(int i=m; i>=l; i--)
    {
        sum=sum+array[i];
        if(sum>left_sum)
            left_sum=sum;
    }
    sum=0;
    int right_sum=INT_MIN;
    for(int i=m+1; i<=r; i++)
    {
        sum=sum+array[i];
        if(sum>right_sum)
                right_sum=sum;
    }
    return max3(left_sum+right_sum, left_sum, right_sum);
}

int maxSumSubarr(int array[], int left, int right)
{
    if(left==right)
        return array[left];
    int m=(left+right)/2;
    return max3(maxSumSubarr(array, left, m),
               maxSumSubarr(array, m+1, right),
               maxCrossingSum(array, left, m, right));
}

int main(int argc, char *argv[])
{
    FILE *fo, *fi;
    for(int j=1; j<argc; j++)
    {
        printf("%s ", argv[j]);
    }
    fi=fopen(argv[1], "r");
    fo=fopen(argv[2], "w");
    int n;
    fscanf(fi, "%d", &n);
    int *array= (int *)malloc(sizeof(int)* n);
    for(int j=0; j<n; j++)
    {
        fscanf(fi, "%d", &array[j]);
    }
    for(int j=0; j<n; j++)
        printf("%d ", array[j]);

    int MAXSUM=maxSumSubarr(array, 0, n-1);
    fprintf(fo, "%d", MAXSUM);

    fclose(fi);
    fclose(fo);
    return 0;
}
