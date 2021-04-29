#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
int A[MAXN];

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

//check if in "right" order
int combineB2S(int left, int right) {//big to small
    int i = left;
    int k = right;

    while(i < k) {
        if(A[i] < A[i+1]) {
            return 0;

        }
        i++;
    }
    return 1;

}
//check if in "right" order
int combineS2B(int left, int right) {//small to big
    int i = left;
    int k = right;

    while(i < k) {
        if(A[i] > A[i+1]) {
                //printf("0\n");
            return 0;
        }
        i++;
    }
    //printf("1\n");
    return 1;

}

int mergeSortS2B(int left, int right) {

    if(left < right) {
        int mid = (left + right) / 2;

        if(!mergeSortS2B(left, mid)) return 0;
        if(!mergeSortS2B(mid + 1, right)) return 0;

        if(!combineS2B(left, right)) return 0;
    }
    return 1;
}

int mergeSortB2S(int left, int right) {

    if(left < right) {
        int mid = (left + right) / 2;

        if(!mergeSortB2S(left, mid)) return 0;
        if(!mergeSortB2S(mid + 1, right)) return 0;

        if(!combineB2S(left, right)) return 0;
    }
    return 1;
}
int main()
{
    int i, n;

    printf("\n Number of elements in vector = ");
    scanf("%d", &n);

    printf("\n Please input vector elements \n");

    for(i = 0; i < n; i++) {
        printf( "a[%d] = ", i);
        scanf("%d", &A[i]);
    }
    if(mergeSortB2S(0,n-1)) {
        printf("Top is:%d\n", A[0]);
    }
    else if(mergeSortS2B(0,n-1)) {
        printf("Top is:%d\n", A[n-1]);
    }
    else
    {
        int ok;
        ok=0;
        i=1;
        while(ok!=1 && i<n-1)
        {
            if(mergeSortS2B(0,i) && mergeSortB2S(i, n-1))
            {
                ok=1;
                printf("Top is:%d\n", A[i]);
            }
            i++;
        }
        if(ok==0 && i==n-1)
        {
            printf("No top\n");
        }
    }
    /*printf("Unsorted vector\n");
    printVector(n);
    mergeSort(0, n-1);
    printf("\nSorted vector\n");
    printVector(n);*/

    while('\n' != getchar());
    return 0;
}
