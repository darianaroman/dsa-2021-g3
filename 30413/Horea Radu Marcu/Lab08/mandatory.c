#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float ceilInt(float a)
{
    if(a == (int) a) return (int) a;
    return (int)a + 1;
}
int main()
{
    int n, m;
    printf("The numbers of the fraction:");
    scanf("%d %d", &n, &m);
    if(n == 1)
    {
        printf("\nThe fraction is already a unit fraction.");
        return 0;
    }
    printf("\nThe fraction %d/%d written as a sum of unit fractions is:", n, m);
    float rez = (float) n / m;
    float rez1 = 1 / rez;
    int first = 1;
    while(rez>0.00001)
    {
        int ceil1 = (int) ceilInt(rez1);
        if(first == 1)
        {
            printf("1/%d", ceil1);
            first = 0;
        }
        else
        {
            printf(" + 1/%d", ceil1);
        }
        rez = rez - (1 / ceilInt(rez1));
        rez1 = 1 / rez;
    }
    return 0;
}
