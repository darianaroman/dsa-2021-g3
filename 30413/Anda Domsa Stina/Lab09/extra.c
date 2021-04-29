#include <stdio.h>
#include <stdlib.h>
void H(int n, char a, char b, char c)
{
    if(n==1)
    {
        printf("%c->%c\n",a,c);
    }
    else
    {
        H(n-1,a,c,b);
        printf("%c->%c\n",a,c);
        H(n-1,b,a,c);
    }
}
int main()
{
   int n;
   scanf("%d",&n);
   H(n,'A','B','C');
    return 0;
}
