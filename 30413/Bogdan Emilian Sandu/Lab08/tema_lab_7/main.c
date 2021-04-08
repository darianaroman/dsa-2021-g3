#include <stdio.h>
#include <math.h>

int cmmmc(int a, int b)
{
    int nr=a*b;
    while(a!=b)
    {
        if(a>b)
            a=a-b;
        else
            b=b-a;
    }
    return nr/a;
}

void greedyEgyptian(int numr, int numi)
{
    int cm,x1,x2;
    float nr;
    while(numr != 1)
    {
        nr = (float)numi/(float)numr;
        //printf("%lf ",nr);
        nr = ceil(nr);
        printf("%d/%d + ", 1, (int)nr);
        cm = cmmmc(numi,(int)nr);
        x1=cm/numi;
        x2=cm/(int)nr;
        numr = numr * x1 - x2;
        numi=cm;
    }
    printf("%d/%d",1,numi);

}

int main() {
    int numr,numi;
    scanf("%d%d",&numr,&numi);
    printf("%d/%d = ",numr,numi);
    greedyEgyptian(numr,numi);
    return 0;
}
