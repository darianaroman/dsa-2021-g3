#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct rational{
    int numerator;
    int denominator;
}rationals;

int cmmdc(int a, int b)
{
    if(b==0)
    {
        return a;
    }
    return cmmdc(b, a%b);
}
int cmmmc (int a, int b)
{
    return (a*b)/cmmdc(a, b);
}
void same_denominator(rationals *px, rationals *py)
{

    px->numerator=px->numerator * (cmmmc(px->denominator, py->denominator) / px->denominator);
    py->numerator=py->numerator * (cmmmc(px->denominator, py->denominator) / py->denominator);
    px->denominator=cmmmc(px->denominator, py->denominator);
    py->denominator=cmmmc(px->denominator, py->denominator);

}
void simplify(rationals *p)
{
    int i;
    for (i=2; i<p->denominator && i<p->numerator; i++)
    {
        if( (p->numerator%i==0) && (p->denominator%i==0) )
        {
            p->numerator/=i;
            p->denominator/=i;
        }
    }
}
int main()
{
    rationals *A= malloc(sizeof(rationals));
    printf("your fraction: ");
    scanf("%d %d", &A->numerator, &A->denominator);
    while (A->numerator>=1)
    {
        int parts= ceil((double )A->denominator / A->numerator);
        rationals *B=malloc(sizeof(rationals));
        B->numerator=1;
        B->denominator=parts;
        printf("\n%d/%d", B->numerator, B->denominator);
        same_denominator(A, B);
        A->numerator=A->numerator - B->numerator;
        simplify(A);
    }
    return 0;
}
