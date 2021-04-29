#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n=8,m=9,i=1,sum,aux;///   n/m
printf("n/m=%.0f/%.0f\n",n,m);
sum=n/m;
sum=ceilf(sum * 100) / 100;
printf("asda%f\n",aux);
while(sum!=0)
    {
        aux=ceilf(1/i * 100) / 100;
        if(sum>=aux)
        {
            aux=1/i;
            aux=ceilf(i * 100) / 100;
            sum=sum-aux;
            sum=ceilf(sum * 100) / 100;
            printf("SUM=%0f\n",sum);
            printf("1/%.0f\n",i);
        }
        i++;
    }
    return 0;
}
