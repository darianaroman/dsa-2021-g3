#include <stdio.h>
#include <stdlib.h>

int min = 1000000;
int n=11;
int v[100] = {15,33,2,31,48,7,9,21,14,3,5,1};


void compute(int v[], int i, int k, int op)
{

   if( k==0 && i<n)
   {
       if(op < min )
           min=op;
       return;
   }

   if(i>=n)
       return;

   compute(v, i+1, k, op);
   compute(v, i+1, k-v[i], op+1);
   compute(v, i+1, k+v[i], op+1);
}

int main()
{

    int a=45, b=97;

    compute(v, 0, b-a, 0);

    if(min==1000000)
        printf("impossible");
    else
        printf(" %d", min);

    return 0;
}
