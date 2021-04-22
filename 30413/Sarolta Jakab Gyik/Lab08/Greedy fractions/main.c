#include <stdio.h>
#include <stdlib.h>
int minim(int x, int y)
{
    if(x < y)
        return x;
    return y;
}
int lowcomMult(int denom, int denom2)
{
    int x = minim(denom, denom2);
    while(1)
    {
        if(x%denom == 0 && x%denom2 == 0)
            return x;
        x++;
    }
}
int greatcomDiv(int x, int y)
{
    if (x == 0)
       return y;
    if (y == 0)
       return x;
    if (x == y)
        return x;
    if (x > y)
        return greatcomDiv(x-y, y);
    return greatcomDiv(x, y-x);
}
void searchFraction(int num, int denom)
{
    int x;
    while((x = greatcomDiv(num, denom)) > 1) //check if the fraction can be simplified
    {
        num /= x;
        denom /= x;
    }
    int aux = num;
        num = denom;
        denom = aux;
    while(denom != 1)
    {
        //swap num, denom

        int val = num/denom;
        printf("1/%d + ", val+1);
        //subtractFraction
        x = lowcomMult(num, val+1);
        denom *= x/num;
        denom = denom - x/(val+1);
        num = x;
        //swap num, denom
        //printf("the num:%d and the denominator:%d\n", num, denom);
    }
    printf("1/%d", num);
}
int main()
{
    int num, denom;
    printf("Introduce a fractional number:\n");
    printf("Numerator:");
    scanf("%d", &num);
    printf("Denominator:");
    scanf("%d", &denom);
    searchFraction(num, denom);
    return 0;
}
