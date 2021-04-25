#include <stdio.h>
#include <stdlib.h>
/// open file if possible
FILE *openCheck (const char *path, const char *mode){
    FILE *pf = fopen(path,mode);
    if (pf == NULL){
        puts("cannot open the file");
        exit(1);
    }
}
/// calculate the maximum of 2 numbers
int max (int a, int b){
    if (a > b) return a;
    return b;
}
/// max sum through midpoint
int maxThroughMid(int A[], int left, int mid, int right){
    int sum = 0;
    int left_sum = -1;
    for (int i = mid; i >= left; i--){
        sum = sum + A[i];
        if (sum > left_sum)
            left_sum = sum;
    }
    sum = 0;
    int right_sum = -1;
    for (int i = mid + 1; i <= right; i++){
        sum = sum + A[i];
        if (sum > right_sum)
            right_sum = sum;
    }
    ///  max(max(a, b), c); - max of 3 numbers
    return max(max(left_sum, right_sum), left_sum + right_sum);
}
/// max on one part
int maxOnePart(int A[], int left, int right){
    if (left == right) /// we have only one element
        return A[left];
    int mid = (left + right) / 2;
    return max(max(maxOnePart(A, left, mid), maxOnePart(A, mid + 1, right)), maxThroughMid(A, left, mid, right));
    /// max for left, max for right, max through mid
}
int main(int argc, char *argv[]){
    FILE *pIn = openCheck(argv[1], "r");
    FILE *pOut = openCheck(argv[2], "w");
    int n;
    fscanf(pIn, "%d", &n);
    int A[n];
    for (int i = 0; i < n; i++)
        fscanf(pIn, "%d", &A[i]);
    int max_sum = maxOnePart(A, 0, n - 1);
    fprintf(pOut, "%d", max_sum);
    fclose(pIn);
    fclose(pOut);
    return 0;
}
