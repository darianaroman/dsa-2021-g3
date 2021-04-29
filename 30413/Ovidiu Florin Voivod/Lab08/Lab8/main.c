#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void vulgarFraction(int num, int denom)
{
    if(num==1 || denom%num==0)
    {
         printf("1/%d",denom/num);
         return;
     /// if num =1 => 1/denom, always
     /// if denom%num=0 => denom=x*num which will finally be written as 1/x
    }
    else
    {
        float revdiv=(float)denom/num;
        int aprox=ceil(revdiv);

        printf("1/%d+",aprox);

        vulgarFraction(num*aprox-denom,denom*aprox);
    }

}
int main()
{

    int numerator, denominator;
    scanf("%d%d",&numerator,&denominator);
    printf("%d/%d=",numerator,denominator);
    vulgarFraction(numerator,denominator);
    return 0;
}
