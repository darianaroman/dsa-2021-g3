#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

// Function to return LCM of two numbers
int leastCommonMultiple(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

int main()
{
    int x, y, aux, lcm;
    char c;
    printf("Please enter a fraction: ");
    scanf("%d%c%d", &x, &c, &y);
    printf("= ");
    while(x != 1)
    {
        double fractionValue = y/x;
        aux = ceil(fractionValue);
        lcm = leastCommonMultiple(aux, y);
        x = x * (lcm/y) - (lcm/aux);
        y = lcm;
        printf("+1/%d ", aux);
    }


}
