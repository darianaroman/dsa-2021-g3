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
    int steps = 0, minim = INT_MAX, c, d;
    while(n > 1)
    {
        //printf("\nn=%d\n", n);
        c = a;
        d = b;
        steps = 0;
        while(c != d)
        {
            int i = 0;
            while(v[i] <= (max(c, d) - min(c, d)) && (i < n))
            {
                i++;
            }
            if(c < d && i == 0)
            {
                c = c + v[i];
                //printf("plus v[%d] = %d\n", i, v[i]);
            }
            else if(c < d)
            {
                c = c + v[i-1];
                //printf("plus v[%d] = %d\n", i-1, v[i-1]);
            }
            else if(i == 0)
            {
                c = c - v[i];
                //printf("minus v[%d] = %d\n", i, v[i]);
            }
            else
            {
                c = c - v[i-1];
                //printf("minus v[%d] = %d\n", i-1, v[i-1]);
            }
            steps++;
        }
        if(steps < minim)
            minim = steps;
        int i = 0;
        while(v[i] <= (max(a, b) - min(a, b)) && (i < n))
        {
            i++;
        }
        n = i - 1;
        //for(int i = 0; i < n; i++)
            //printf("%d ", v[i]);
    }

    return minim;
}
int turnNumber2(int a, int b, int *v, int n)
{
    int ind = n, minim = INT_MAX, c, d, steps;
    //printf("\nn=%d\n", n);
    c = a;
    d = b;
    steps = 0;
    while(c != d)
    {
        int i = ind-1;
        while(v[i] > (max(c, d) - min(c, d)) && (i >= 0))
        {
            i--;
        }
        if((v[i] != (max(c, d) - min(c, d)) && (i != ind-1)) || (i == -1))
            i++;
        ind  = i;
        if(c < d)
        {
            c = c + v[i];
            //printf("plus v[%d] = %d\n", i, v[i]);
        }
        else
        {
            c = c - v[i];
            //printf("minus v[%d] = %d\n", i, v[i]);
        }
        steps++;
    }
    if(steps < minim)
        minim = steps;
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
    n--; //because of the new line character at the end of the in.txt file it puts a garbage value on the last position
    bubblesort(v, n);
    int min1 = turnNumber(A, B, v, n);
    printf("\nThe number of steps needed for only + or -: %d\n", min1);

    int min2 = turnNumber2(A, B, v, n);
    printf("\nThe number of steps needed for + and - simultanously: %d\n", min2);

    printf("\nThe minimum number of steps needed: %d\n", min(min1, min2));
    fclose(f);
    return 0;
}
