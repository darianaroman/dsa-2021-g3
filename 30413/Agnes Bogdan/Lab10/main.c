/*Two natural numbers, say A and B, and a vector v containing natural numbers are given. Show how B can be
obtained from A using the values of vector v and the following operations:
a) Add to A any number of elements from v.
b) Subtract from A any number of elements from v.
Each element of v may be used for any number of times. If such solutions are possible, find the minimum number
of operations which give the result B starting with the value A. I/O description. Input: A and B on one line,
elements of vector v on another. Field separator is space. Output: 0 if no solution, minimum number of operations
otherwise. E.g. Input:
45 97
15 33 2 31 48 7 9 21 14 3 5 1*/


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int A, B, i, n, p, j, nr;
    FILE *f = fopen("in.txt", "r");
    int *v = (int*)malloc(sizeof(int));
    int a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11;

    fscanf(f, "%d %d", &A, &B);
    printf("A = %d\nB = %d", A, B);
    i = 0;
    while(fscanf(f, "%d", v + i) == 1)
    {
        i++;
        v = realloc(v, (i+1) * sizeof(int));
        //a = realloc(a, (i+1) * sizeof(int));
        n = i;
    }
    for(i = 0; i < n; i++)
        for(j = i; j < n-1; j++)
        if( v[i] < v[j])
        {
            p = v[i];
            v[i] = v[j];
            v[j] = p;
        }
    for(i = 0; i < n; i++)
    {
        printf("\nv[%d] = %d", i, *(v + i));
    }
    /*v[0] = 48 - 1 ///52
    v[1] = 33 - 1
    v[2] = 31 - 1
    v[3] = 21 - 2
    v[4] = 15 - 3
    v[5] = 14 - 3
    v[6] = 9 - 5
    v[7] = 7 - 7
    v[8] = 5 - 10
    v[9] = 3 - 17
    v[10] = 2 -26
    v[11] = 1 - 52*/
    nr = 0;
    int min= 52;
    for(a0 = 0; a0 <= 1 ; a0++)
    for(a1 = 0; a1 <= 1 ; a1++)
    for(a2 = 0; a2 <= 1 ; a2++)
    for(a3 = 0; a3 <= 2 ; a3++)
    for(a4 = 0; a4 <= 3 ; a4++)
    for(a5 = 0; a5 <= 3 ; a5++)
    for(a6 = 0; a6 <= 5 ; a6++)
    for(a7 = 0; a7 <= 7 ; a7++)
    for(a8 = 0; a8 <= 10 ; a8++)
    for(a9 = 0; a9 <= 17 ; a9++)
    for(a10 = 0; a10 <= 26 ; a10++)
    for(a11 = 0; a11 <= 52 ; a11++)
    if(a0 * 48 + a1 * 33 + a2 * 31 + a3 * 21 + a4 * 15 + a5 * 14 + a6 * 9 + a7 * 7 + a8 * 5 + a9 * 3 + a10 * 2 + a11 * 1 == 52)
        if(a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a7 + a8 + a9 + a10 + a11 <= min)
        {
            min = a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11;
            printf("\n%d %d %d %d %d %d %d %d %d %d %d %d", a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
        }
    printf("\nmin = %d", min);
    free(v);
    return 0;
}
