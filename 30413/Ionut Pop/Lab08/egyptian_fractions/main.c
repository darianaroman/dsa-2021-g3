#include <stdio.h>
#include <stdlib.h>

int Ceil(int x, int y){
    return x/y+1;
}

int Floor(int x, int y){
    return x/y;
}

int min(int x, int y){
    if (x<y)
        return x;
    return y;
}

int lcm(int x, int y){    //least common multiple
    int m=min(x, y);
    while((m%x==0 && m%y==0)==0)
        ++m;
    return m;
}

int main()
{
    int x, y;

    printf("enter the numenrator: ");
    scanf("%d", &x);
    printf("enter the denominator: ");
    scanf("%d", &y);
    printf("\n");

    printf("1");
    //printf("\nx:y=");


    while (x!=1){
        printf("1");
        int c=Ceil(x, y);
        printf("1/%d + ", c);
        y=lcm(x, y);
        x=x*(y/c)-y/c;
    }
    printf("1/%d", y);



    return 0;
}
