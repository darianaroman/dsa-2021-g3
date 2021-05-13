#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int min2(int a, int b)
{
    return (a <= b)? a:b;
}

int min3(int a,int b,int c)
{
    return min2(min2(a,b),c);
}


int Dyn(char cuv1[],char cuv2[],int lung1,int lung2)
{

    int dyn[lung1+1][lung2+1];
    int i,j;
    for(i=0;i<=lung1;i++)
    {
        for(j=0;j<=lung2;j++)
        {
            if( i==0 )
                    dyn[i][j]= j;
               else
            if( j==0 ) dyn[i][j]= i;
               else
            if( cuv1[lung1-1]==cuv2[lung2-1] ) dyn[i][j]= dyn[i-1][j-1];
               else
                dyn[i][j]= 1+ min3( dyn[i-1][j], dyn[i][j-1], dyn[i-1][j-1]);
        }
    }
    return dyn[lung1][lung2];
}

int main()
{
    int dyn;
    char cuv1[]="sunday",cuv2[]="saturday";
    int lung1=strlen(cuv1), lung2=strlen(cuv2);

    dyn= Dyn(cuv1,cuv2,lung1,lung2);
    printf("\nThe minimum number of operations needed is %d",dyn);

    return 0;
}
