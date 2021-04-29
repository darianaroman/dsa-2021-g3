#include <stdio.h>
#include <stdlib.h>

int cmmdc( int a, int b )
{
    int r;
    while( b != 0 )
    {
        r= a%b;
        a= b;
        b= r;
    }
    return a;
}


int* simplificare(int n, int d)
{
    int c,v[2];
    c= cmmdc(n,d);
    if( c!=1 )
    {
        n= n/c;
        d= d/c;
    }
    v[0]=n; v[1]=d;
    return *v;
}

int minus( int n, int d, int n1, int d1 )
{
   n = d1*n - d*n1;
   d *= d1;
   int v[2];
   *v=simplificare(n,d);
   v[0]=n; v[1]=d;
   return *v;
}

void factors(int n,int d)
{
    int n1,d1,v[2];
    int k=0;
    printf("%d/%d = ",n,d);
    while( n!=0 )
    {
        if( k!=0 ) printf(" + ");
        n1= 1;
        d1= d/n;
        d1++; ///ceil value
        printf("%d/%d",n1,d1);
        *v= minus(n,d,n1,d1);
        v[0]=n; v[1]=d;
        k++;
    }
}

int main()
{
    int n,d;
    while(getchar()!='q')
    {
        printf("\nComputing vulgar fractions (n<d):");
        printf("\nEnter numerator for the fraction (n) : ");
        scanf("%d",&n);
        printf("\nEnter denominator for the fraction (d) : ");
        scanf("%d",&d);
        if( d<n ) printf("\nThis is not a vulgar fraction, try again.");
           else
               factors(n,d);
        getchar();
        printf("\n\nDo you want to quit? Press q if yes or enter to continue.\n\n");
    }
    return 0;
}
