#include <stdio.h>
#include <stdlib.h>
int summax = 0;
int initializat = 0;
void sum(int left, int mid, int right,int *a)
{
    if(initializat == 0)
    {
        initializat = 1;
        summax = a[left];
    }
    int s = 0;
    int i = left;
    while(i <= mid)
    {
        if(s > 0) s += a[i];
        else s = a[i];
        if(s > summax) summax = s;
        i++;
    }
    if(s > 0)
    {
        while(i <= right)
        {
        if(s > 0) s += a[i];
        else s = a[i];
        if(s > summax) summax = s;
        i++;
        }
    }
    else
    {
        s = 0;
        while(i <= right)
        {
        if(s > 0) s += a[i];
        else s = a[i];
        if(s > summax) summax = s;
        i++;
        }
    }
}
void Divide(int left, int right,int *a)
{
    int mid=(left + right) / 2;
    if(left < right)
    {
        Divide(left, mid, a);
        Divide(mid + 1, right, a);
    }
    sum(left, mid, right, a);
}
int main(int argc,char *argv[])
{
    FILE *f = fopen(argv[1],"r");
    FILE *fout = fopen(argv[2],"w");
    int n,i;
    fscanf(f, "%d", &n);
    int *a = (int*)malloc(n*sizeof(int));
    for(i = 0;i < n; i++)
    {
        fscanf(f,"%d", &a[i]);
    }
    int l=0,r=n-1;
    Divide(l,r,a);
    fprintf(fout, "The maximum sum of the given array is: %d", summax);
    return 0;
}
