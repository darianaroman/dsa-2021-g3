#include <stdio.h>
#include <stdlib.h>

int n;
int min = 1000000;
int v[1000];

void opMin(int v[], int i, int k, int op)
{

   if(k == 0 && i < n)
   {
       if(op < min )
           min = op;
       return;
   }

   if(i >= n)
       return;

   opMin(v, i + 1, k, op);
   opMin(v, i + 1, k - v[i], op + 1);
   opMin(v, i + 1, k + v[i], op + 1);
}

int main()
{
    int a , b;
    scanf("%d%d",&a,&b);
    printf("Nr of vector's elements:");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&v[i]);
    opMin(v, 0, b-a, 0);

    if( min == 1000000 )
        printf("0--No solution!");
    else
        printf("The minimum number of operations is: %d", min);

    return 0;
}
