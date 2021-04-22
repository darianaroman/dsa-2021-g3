#include <stdio.h>
#include <stdlib.h>

void money(int sum)
{
    int v[10]={500,200,100,50,10,5,1};
    int a[10];
    int i;
    for(i=0;i<7;i++)
    {
        a[i]=sum/v[i];
        sum=sum-a[i]*v[i];
        if(a[i]!=0)
        {
            printf(" %d*%d +",a[i], v[i]);
        }
    }
    printf("%c",(char)8);
    printf(" ");
}
int main()
{
  int sum;
  scanf("%d",&sum);
  printf("%d=", sum);
  money(sum);
  return 0;
}
