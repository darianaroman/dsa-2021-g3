#include <stdio.h>
#include <stdlib.h>

int ceil_inv (int x, int y)
{
    return y/x+1;
}
int cmmdc (int x, int y)
{
    while(x!=y)
    {
        if(x>y)
            x=x-y;
        else
            y=y-x;
    }
    return x;
}
int cmmmc(int x, int y)
{
    return x*y/cmmdc(x,y);
}
int egip_funct(int x, int y)
{
    if (x==1)
    {
        printf(" 1/%d\n",y);
        return 0;
    }
    else
    {
        int a=ceil_inv(x,y);
        printf(" 1/%d +",a);
        int x1=x*a/cmmdc(y,a)-y/cmmdc(y,a), y1=cmmmc(y,a);
        return egip_funct(x1,y1);

    }

}
void afisare(int x, int y)
{
    printf("\n%d/%d = ",x,y);
}
int main()
{
    int x,y;
    printf("Introduce the numerator of the function: ");
    scanf("%d",&x);
    printf("\nIntroduce the denominator of the function: ");
    scanf("%d",&y);
    afisare(x,y);
    egip_funct(x,y);
    return 0;
}
