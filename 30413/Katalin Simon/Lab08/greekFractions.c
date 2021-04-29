#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n,d,r;
    printf("provide the numerator:");
    scanf("%d",&n);
    printf("the numerator is:%d\n",n);
    printf("provide the denominator:");
    scanf("%d",&d);
    printf("the denominator is:%d\n",d);
    float f,c;
    f=((float) (n))/((float) (d));
    printf("%d/%d=",n,d);
    c=ceil(((float) (d))/n);
    r=((int)(c));
    printf("1/%d",r);
    n=n*r-d;
    d=r*d;
    f=((float) (n))/((float) (d));
    //printf("the fraction is:%f\n",f);
    while(f!=0)
    {
        c=ceil(((float) (d))/n);
        //printf("f is:%f\n",((float) (d))/n);
        //printf("the ceil is:%f\n",c);
        r=((int)(c));
        printf("+1/%d",r);
        n=n*r-d;
        d=r*d;
        f=((float) (n))/((float) (d));
        //printf("the fraction is:%f\n",f);
    }
    return 0;
}
