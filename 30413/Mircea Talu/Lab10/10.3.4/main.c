#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INF 1000000000

int a, b, nr;
int S[100];

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int smaller(int x, int y)
{
    if(x < y)
        return x;
    else
        return y;
}

int minimumOperations(int X[], int sz, int nr)
{
    int Val[10000];
    for(int i = 0; i <= nr; i++)
        Val[i] = INF;
    for(int i = 1; i <= nr; i++)
    {
        for(int j = 0; j < sz; j++)
        {
            if(abs(X[j]) <= i)
                Val[i] = smaller(Val[i], 1 + Val[i - X[j]]);
        }
    }
    if(Val[sz] == INF)
        return 0;
    return Val[nr];
}

/*int step(int x)
{
    if(x < -10)
    {
        return 0;
    }
    if(x == a)
    {
        return 1;
    }
    else
    {
        for(int i = 0; S[i] != 0; i++)
            step(x - S[i]);
    }
    return 0;
}
*/

int main()
{
    scanf("%d %d %d", &a, &b, &nr);
    int diff = abs(a - b);
    for(int i = 0; i < nr; i++)
        scanf("%d", &S[i]);

    /*for(int i = 0; i < 2 * n; i = i + 2)
    {
        scanf("%d", &S[i]);
        S[i+1] = -S[i];
    }
    if(step(b) == 1)
        printf("success");
    for(int i = 0; i < sizeof(S); i++)
        printf("%d ", S[i]);
    */
    qsort(S, sizeof(S), sizeof(int), cmpfunc);
    printf("%d", minimumOperations(S, nr, diff));
    return 0;
}
