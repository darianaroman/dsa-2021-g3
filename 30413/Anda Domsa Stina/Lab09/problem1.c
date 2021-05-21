#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max3(int a, int b, int c)
{
    int mx=a;
    if(mx<b)
    {
        mx=b;
    }
    if(mx<c)
    {
        mx=c;
    }
    return mx;
}

int sumcross(int v[], int lt,int m, int rt)
{
    int i, sum_lt=INT_MIN, sum_rt=INT_MIN, sum=0;
    for(i=m; i>=lt; i--)
    {
        sum=sum+v[i];
        if(sum>sum_lt)
        {
            sum_lt=sum;
        }
    }
    sum=0;
    for(i=m+1; i<=rt; i++)
    {
        sum=sum+v[i];
        if(sum>sum_rt)
        {
            sum_rt=sum;
        }
    }
    return max3(sum_lt,sum_rt,sum_lt+sum_rt);
}

int summax(int v[],int lt, int rt)
{
    int m,a,b,c;
    if(lt==rt)
    {
        return v[1];
    }
    else if(lt<rt)
    {
        m=(lt+rt)/2;
        a=summax(v,lt,m);
        b=summax(v,m+1,rt);
        c=sumcross(v,lt,m,rt);
        return max3(a,b,c);
    }
    else
    {
        return 0;
    }
}
int main()
{
    int n,max_sum;
    int v[101];
    int i;

    printf("Number of elements:");
    scanf("%d",&n);
    printf("\nElements:");
    for(i=0; i<n; i++)
    {
        scanf("%d",&v[i]);
    }

    max_sum=summax(v,0,n-1);
    printf("\nMaximum Sum: %d",max_sum);

    return 0;
}
