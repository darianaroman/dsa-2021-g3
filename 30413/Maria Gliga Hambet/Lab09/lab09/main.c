#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxim(int a, int b)
{
      if(a>b) return a;
      else return b;
}

int sum(int l, int m, int r, int *arr)
{
    int maxLsum=INT_MIN,maxRsum=INT_MIN;
    int sum=0,i;
    for(i=m;i>=l; i--)
       {
           sum=sum+arr[i];
           if(sum>maxLsum) maxLsum=sum;
       }
    sum=0;
    for(i=m+1;i<=r;i++)
    {
        sum=sum+arr[i];
        if(sum>maxRsum) maxRsum=sum;
    }
    return(maxim(maxim(maxRsum,maxLsum),maxLsum+maxRsum));
}

int divideConquer(int l, int r, int *arr)
{
    int m=(l+r)/2;
    if(l==r) return arr[l];
    return maxim(maxim(divideConquer(l,m,arr),divideConquer(m+1,r,arr)),sum(l,m,r,arr));

}
int main()
{
    int *v,n,i;
    FILE* fi=fopen("data.in","r");
    FILE* fo=fopen("data.out","w");
    fscanf(fi,"%d",&n);
    v = (int*) malloc(n * sizeof(int));
    for( i=0;i<n;i++) fscanf(fi,"%d",&v[i]);
    fprintf(fo,"The maximum subarray sum is %d\n",divideConquer(0,n-1,v));
    free(v);
    return 0;
}
