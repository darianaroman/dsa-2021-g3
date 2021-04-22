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

void combine(int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int B[MAXN];
    int k = left;

    while(i <= mid && j <= right) {
        if(A[i] <= A[j]) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }

        k++;
    }

    int v = 0;

    for(v = i; v <= mid; v++) {
        B[k] = A[v];
        k++;
    }

    for(v = j; v <= right; v++) {
        B[k] = A[v];
        k++;
    }

    for(v = left; v <= right; v++) {
        A[v] = B[v];
    }

}

void mergeSort(int left, int right) {

    if(left < right) {
        int mid = (left + right) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        combine(left, mid, right);
    }
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

    printf("Unsorted vector\n");
    printVector(n);
    mergeSort(0, n-1);
    printf("\nSorted vector\n");
    printVector(n);

    while('\n' != getchar());
    return 0;
}
