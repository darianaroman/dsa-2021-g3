#include <stdio.h>
#include <stdlib.h>
void fractions(int a, int b)
{
    if(a==0||b==0)
    {
        return;
    }
    if(b%a==0)
    {
        printf("1/%d ", b/a);
        return;
    }
    if(a%b==0)
    {
        printf("%d ", a/b);
        return;
    }
    if(a>b)
    {
        printf("%d +", a/b);
        fractions(a%b,b);
        return;
    }
    if(a<b)
    {
        int c;
        c=b/a+1;
        printf("1/%d +",c);
        fractions(a*c-b,b*c);
    }
}
int main()
{
    int a=5,b=4;
    printf("%d/%d=",a,b);
    fractions(a,b);
    return 0;
}
