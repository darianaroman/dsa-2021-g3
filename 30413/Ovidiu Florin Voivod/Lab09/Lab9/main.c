#include <stdio.h>
#include <stdlib.h>

int maxim(int a, int b)
{
      return (a > b ) ? a : b;
}

int sum(int left, int mid, int right, int *arr)
{
    int maxLsum=-1000,maxRsum=-1000;
    int sum=0,i;
    //int maxleft,maxright;
    for(i=mid;i>=left; i--)
       {
           sum+=arr[i];
           if(sum>maxLsum) maxLsum=sum;
       }
    sum=0;
    for(i=mid+1;i<=right;i++)
    {
        sum+=arr[i];
        if(sum>maxRsum)
            maxRsum=sum;
    }
    return(maxim(maxim(maxRsum,maxLsum),maxLsum+maxRsum));
}

int divideConquer(int left, int right, int *arr)
{
    int m=(left+right)/2;
    if(left==right) return arr[left];
    return maxim(maxim(divideConquer(left,m,arr),divideConquer(m+1,right,arr)),sum(left,m,right,arr));



   //return sum(left,m,right,arr);
}
int main()
{
    int v[100],n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&v[i]);
    printf("%d\n",divideConquer(0,n-1,v));
   //int x=sum(0,(n-1)/2,n-1,v);
   //printf("%d",x);
    return 0;
}
