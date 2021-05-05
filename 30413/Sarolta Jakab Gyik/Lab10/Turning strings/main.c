/*Two natural numbers, say A and B, and a vector v containing natural numbers are given. Show how B can be obtained from
A using the values of vector v and the following operations:
a) Add to A any number of elements from v.
b) Subtract from A any number of elements from v.
Each element of v may be used for any number of times. If such solutions are possible, find the minimum number
of operations which give the result B starting with the value A. I/O description. Input: A and B on one line,
elements of vector v on another. Field separator is space. Output: 0 if no solution, minimum number of operations otherwise*/
#include <stdio.h>
#include <stdlib.h>

void bubblesort(int *v, int n)
{
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++)
            if(v[i] > v[j]) ///encreasing order
            {
                int c = v[i];
                v[i] = v[j];
                v[j] = c;
            }
}
int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
int min(int a, int b)
{
    if(a>b)
        return b;
    return a;
}
int turnNumber(int a, int b, int *v, int n)
{
    int steps = 0;
    while(a != b)
    {
        int i = 0;
        while(v[i] <= (max(a, b) - min(a, b)) && (i < n))
        {
            i++;
        }
        if(a < b && i == 0)
        {
            a = a + v[i];
            ///printf("plus v[%d] = %d\n", i, v[i]);
        }
        else if(a < b)
        {
            a = a + v[i-1];
            ///printf("plus v[%d] = %d\n", i-1, v[i-1]);
        }
        else if(i == 0)
        {
            a = a - v[i];
            ///printf("minus v[%d] = %d\n", i, v[i]);
        }
        else
        {
            a = a - v[i-1];
            ///printf("minus v[%d] = %d\n", i-1, v[i-1]);
        }
        steps++;
    }
    return steps;
}
int main(int argc, char const *argv[])
{
    FILE* f = fopen(argv[1], "r");
    int A, B, *v, n = 0;

    fscanf(f, "%d%d", &A, &B);
    v = (int*) malloc(sizeof(int));
    fscanf(f, "%d", &v[n]);
    while(v[n] != 0)
    {
        n++;
        v = (int*) realloc(v, (n+1) * sizeof(int));
        fscanf(f, "%d", &v[n]);
    }
    bubblesort(v, n-1);
    for(int i = 0; i < n-1; i++)
        printf("%d ", v[i]);
    printf("\nThe number of steps needed: %d\n", turnNumber(A, B, v, n-1));
    fclose(f);
    return 0;
}
