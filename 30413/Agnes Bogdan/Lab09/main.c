#include <stdio.h>
#include <stdlib.h>
//-2 -5 6 -2 -3 1 5 -6
void maxSubarray(int a[], int nr)
{
    int i, max, temp_max, A[15],j, nr2;
    max = a[0];
    temp_max = a[0];
    A[0] = a[0];
    j = 0;
    for(i = 1; i < nr; i++)
    {
        if(temp_max + a[i] > a[i])
        {
            j++;
            temp_max = temp_max + a[i];
            A[j] = a[i];

        }
            else {
                temp_max = a[i];
                A[0] = a[i];
                j = 0;
            }
        if(temp_max > max) max  = temp_max;
    }
    nr2 = j;
    printf("the maximum sum of a subarray is = %d\nand the array is:", max);
    for(j = 0; j < nr2; j++)
        printf("%d ", A[j]);
}
int main()
{
    int a[15], nr, aux, i;
    FILE *f = fopen("in.txt", "r");

    i = 0;
    while(fscanf(f, "%d ", &aux) == 1)
    {
        a[i] = aux;
        i++;
    }
    nr = i;
    maxSubarray(a, nr);
    return 0;
}
