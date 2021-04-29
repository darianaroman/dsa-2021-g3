#include <stdio.h>
#include <stdlib.h>

int maxMidSum (int arr[], int l, int h, int mid)
{
    int sum = 0, leftSum = -1000, rightSum = -1000, i;
    for (i = mid; i >= l; i--) {
      sum += arr[i];
      if (sum > leftSum) {
        leftSum = sum;
      }
    }

    sum = 0;
    for (i = mid + 1; i <= h; i++) {
      sum += arr[i];
      if (sum > rightSum) {
        rightSum = sum;
      }
    }

    return (leftSum + rightSum) * (leftSum + rightSum > leftSum && leftSum + rightSum > rightSum) + leftSum * (leftSum > rightSum && leftSum >= leftSum + rightSum) + rightSum * (rightSum >= leftSum && rightSum >= leftSum + rightSum);
}

int maxSum (int arr[], int l, int h)
{
    if (l == h) {
      return arr[l];    /// if the subarray has one element that will be the max sum of the subarray
    }

    int mid = (l + h) / 2;

    int left = maxSum(arr, l, mid);
    int right = maxSum(arr, mid + 1, h);
    int midSum = maxMidSum(arr, l, h, mid);

    return left * (left > right && left > midSum) + right * (right >= left && right > midSum) + midSum * (midSum >= left && midSum >= right);
}

int main(int argc, char *argv[])
{
///    FILE *fileI = fopen(argv[1], "w");
    FILE *fileO = fopen(argv[2], "w");
    int arr[9] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int lenght = sizeof(arr) / sizeof (arr[0]);
    fprintf(fileO, "maximmum sum is: %d", maxSum(arr, 0, lenght - 1));
    return 0;
}
