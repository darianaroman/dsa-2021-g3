#include <stdio.h>
#include <stdlib.h>


int max2(int a, int b)
{ return (a > b) ? a : b; }



int max3(int a, int b, int c)
{ return max2(max2(a, b), c); }




int maxCrossingSum(int arr[], int l, int m, int h)
{
    // Include elements on left of mid.
    int sum = 0;
    int lsum = -100000;
    for (int i = m; i >= l; i--)
    {
        sum = sum + arr[i];
        if (sum > lsum)
            lsum = sum;
    }



    sum = 0;
    int rsum = -100000;
    for (int i = m + 1; i <= h; i++) {
        sum = sum + arr[i];
        if (sum > rsum)
            rsum = sum;
    }



    return max3(lsum + rsum, lsum, rsum);
}



int sumaa(int arr[], int l, int h)
{
    if (l == h)
        return arr[l];
    int m = (l + h) / 2;



    return max3(sumaa(arr, l, m),sumaa(arr, m + 1, h),maxCrossingSum(arr, l, m, h));
}




int main()
{
    int n,v[100];



    printf("\nInput number of elements in array: ");
    scanf("%d",&n);



    printf("\nInput elements: ");
    for(int i=0;i<n;i++)
        scanf("%d",&v[i]);
    getchar();



    int max_sum = sumaa(v, 0, n - 1);
    printf("\nMaximum sum is %d", max_sum);




    return 0;
}
