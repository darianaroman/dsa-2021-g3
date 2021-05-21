#include <stdio.h>
#include <stdlib.h>
int maximum(int a, int b,int c){ ///made to find out the maximum of the left side, right side and the middle side
      if(a>b&&b>c)
        return a;
      else
        if(b>a&&b>c)
            return b;
        else
            return c;
}

int maximumSum(int left, int mid, int right, int array[]){ ///to find the maximum sum of the left side, right side and the middle side
    int maxLeft=-1000,maxRight=-1000;
    int sum=0,i;
    for(i=mid;i>=left; i--)
       {
           sum=array[i]+sum;
           if(sum>maxLeft)
            maxLeft=sum;
       }
    sum=0;
    for(i=mid+1;i<=right;i++)
    {
        sum+=array[i];
        if(sum>maxRight)
            maxRight=sum;
    }
    return(maximum(maxLeft,maxRight,maxLeft+maxRight));
}

int divideAndConquer(int left, int right, int array[])
{
    int m=(left+right)/2;
    if(left==right) return array[left];
    return maximum(divideAndConquer(left,m,array),divideAndConquer(m+1,right,array),maximumSum(left,m,right,array));
}
int main()
{
    int a[100],n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    printf("%d\n",divideAndConquer(0,n-1,a));
    return 0;
}
