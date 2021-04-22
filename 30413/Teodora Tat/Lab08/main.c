#include <stdio.h>
#include <stdlib.h>
void fraction(float a, float b)
{float n;
n=a/b;
float i=2;
float nr=0;
printf("%.0f", a);
printf(" / %.0f", b);
printf(" = ");
    while(n>0)
    {nr=(float)1/i;
        if(n>=nr)
        {
            n=n-nr;
            printf("+ 1/  %.0f ", i);
            i++;
        }
        else
        {i++;}
    }
}
int main()
{
    float x=3, y=8;
    fraction(x,y);
    return 0;
}
