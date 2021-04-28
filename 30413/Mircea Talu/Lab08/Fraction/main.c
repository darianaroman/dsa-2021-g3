#include <stdio.h>
#include <stdlib.h>

void godlike(int a, int b, int i)
{
    if(a == 1)
    {
        printf("%d/%d", a, b);
        return;
    }
    if(a * i < b)
    {
        godlike(a, b, i + 1);
    }
    else
    {
        printf("1/%d ", i);
        godlike(a * i - b, b * i, i + 1);
    }
}

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    godlike(a, b, 1);
    return 0;
}
