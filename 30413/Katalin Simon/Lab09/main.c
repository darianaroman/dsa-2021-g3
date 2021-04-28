#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXN 100
int A[MAXN],sum=INT_MIN;

void printVector(int n) {
    int i;

    for(i = 0; i < n; i++) {
        printf("%5d ", A[i]);
    }
}

void printVectorBound(int left, int right) {
    int i;

    for(i = left; i <= right; i++) {
        printf("%5d ", A[i]);
    }
}

void arraysum(int left, int right) {
    int i = left;
    int k = right;
    int partARRSum=0;

    for(i; i<=k; i++)
    {
        partARRSum+=A[i];//sum of subarray elements
    }
    //printVectorBound(left, right);
    //printf("\nSum=%d\n", partARRSum);
    if(partARRSum>sum) sum=partARRSum;//calculating sum

}
void mergeSort(int left, int right) {

    if(left < right) {
        int mid = (left + right) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        //arraysum(left, right);
    }
    arraysum(left, right);//otherwise does not consider 1 element arrays
}

int main()
{
    printf("Hello world!\n");
    int arr[6] = {1, 2, 3, 4, 5, 6};

    int i, n;

    printf("\n Number of elements in vector = ");
    scanf("%d", &n);

    printf("\n Please input vector elements \n");

    for(i = 0; i < n; i++) {
        printf( "a[%d] = ", i);
        scanf("%d", &A[i]);
    }

    int p, q;
    for(p=0; p<=n-1; p++)
        for(q=p; q<=n-1; q++)
            mergeSort(p,q);
    printf("\nSum=%d\n", sum);
    while('\n' != getchar());
    return 0;
}
