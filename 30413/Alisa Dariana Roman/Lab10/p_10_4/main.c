/** algorithm:
- to get from a to b we need to find minimum number of operations to obtain
  x = abs(b - a) using the elements of the vector

- I initialized an array from 0 to x + 1 where I save the minimum number
  of operations needed for each number in that range: starting from 1 to x

- dp[0] is initialized as 0 in order to start the algorithm
**/
#include <stdio.h>
#include <stdlib.h>
#define MAX_INT 999
#define MAX_ARR 200

int computeMinOp(int x, int v[], int n)
{
  int i, j;
  int dp[x+1];
  int num;
  dp[0] = 0;
  for (i = 1; i <= x; i ++) {
    dp[i] = MAX_INT;
    for (j = 0; j < n; j ++) {
      if (i >= v[j]) {
        num = dp[i - v[j]] + 1;
        if (num < dp[i]) {
          dp[i] = num;
        }
      }
    }
  }
  return dp[x];
}

int main()
{
  int a = 45, b = 97;
  int v[] = {15, 33, 2, 31, 48, 7, 9, 21, 14, 3, 5, 1};
  int n = 12;
  int x = abs(b - a);

  // int v[] = {6, 5, 1};
  // int n = 3;
  // int x = 9;

 // int v[] = {20, 27, 60};
 // int n = 3;                  /// not working
 // int x = 53;

  printf("\nmin is %d\n", computeMinOp(x, v, n));
  return 0;
}
