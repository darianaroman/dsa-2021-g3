/*Given a one dimensional array that may contain both positive and negative integers, find the sum of contiguous
subarray of numbers which has the largest sum.
I/O description. Input. One line of space-separated integers, where the first integer is the number of elements in
the sequence.
Output. The value of maximum subarray sum.*/

#include <stdio.h>
#include <stdlib.h>
#define MAXN 100
int A[MAXN];
void printVector(int n) /* print vector elements- 10 on one line*/
{
    int i;
    printf("\n");
    for(int i = 0; i < n; i++)
    {
        printf("%5d", A[i]);
        if((i+1)%10 == 0)
            printf("\n");
    }
    printf("\n");
}
int maxSubarray(int left, int right, int *k, int *l)
{
    int max = INT_MIN, maxcurr = A[0];
    *k = left;
    *l = left;
    for(int i = left+1; i <= right; i++)
    {
        if(A[i] > max && (A[i]+max < A[i]))
        {
            max = A[i];
            *k = i;
            *l = i;
        }
        else if(max + A[i] > max)
        {
            max += A[i];
            *l = i;
        }
    }
    return max;
}
int maxNr(int x, int y)
{
    return (x > y)? x : y;
}

int divideEtImpera(int n)
{
    if(!n)
    {
        printf("The array is empty\n");
        return NULL;
    }
    if(n == 1)
        return A[0];

    int mid = n/2, midMax = 0;
    int *k = (int*)malloc(sizeof(int));
    int *l = (int*)malloc(sizeof(int));
    int maxi1 = maxSubarray(0, mid-1, k, l);
    int ind1 = *l;
    int maxi2 = maxSubarray(mid, n-1, k, l);
    int ind2 = *k + mid;
    int maxArrays = maxNr (maxi1, maxi2);
    midMax = maxArrays;
    for(int i = ind1+1; i < ind2; i++)
        midMax += A[i];
    free(k);
    free(l);
    return maxNr(maxArrays, midMax);
}
int main(int argc, char const *argv[])
{
    FILE *f = fopen(argv[1], "r");
    int n;
    fscanf(f, "%d", &n);
    for(int i = 0; i < n; i++)
        fscanf(f, "%d", &A[i]);
    printVector(n);
    printf("The sum of the maximal subarray is: %d\n", divideEtImpera(n));
    fclose(f);
    return 0;
}
