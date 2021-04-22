//m/n = 1/x + 1/y +....
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int subtractNumerator(int a, int b, int c, int d)
{
    int m;
    m = a*d - b*c;
    return m;
}

int subtractDenominator(int a, int b, int c, int d)
{
    int n;
    n = b*d;
    return n;
}

int ceilValue(int m, int n)
{
    float ceilValue;
    ceilValue = ceil((float)n / m);
    return ceilValue;
}

void expand(int M, int N)
{
    float cValue;
    cValue = ceilValue(M, N);
    printf("1 / %d ", (int)cValue);
    M = subtractNumerator(M, N, 1, (int)cValue);
    N = subtractDenominator(M, N, 1, (int)cValue);
    //printf("\n%d / %d = ", M, N);
    while(M != 0)
    {
        cValue = ceilValue(M, N);
    printf("+ 1 / %d ", (int)cValue);
    M = subtractNumerator(M, N, 1, (int)cValue);
    N = subtractDenominator(M, N, 1, (int)cValue);
    }
}

int main()
{
    int N, M, n, m;
    float cValue;
    printf("write the two numbers you want to divide: ");
    scanf("%d%d", &M, &N);
    printf("%d / %d = ", M, N);
    expand(M, N);
    return 0;
}
