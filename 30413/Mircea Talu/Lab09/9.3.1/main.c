#include <stdio.h>
#include <stdlib.h>

int max(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

int maximum_sum(int A[], int left, int right)
{
    if (left == right)
    {
        return A[left];
    }
    int mid = (left + right) / 2;
    int left_max = INT_MIN;
    int sum = 0;
    for (int i = left; i <= mid; i--)
    {
        sum = sum + A[i];
        if (sum > left_max)
        {
            left_max = sum;
        }
    }
    int right_max = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= right; i++)
    {
        sum = sum + A[i];
        if(sum > right_max)
        {
            right_max = sum;
        }
    }
    int max_left_right = max(maximum_sum(A, left, mid), maximum_sum(A, mid + 1, right));
    return max(max_left_right, left_max + right_max);
}

int main()
{
    int n;
    int A[100];
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    printf("%d", maximum_sum(A, 0, n - 1));
    return 0;
}
