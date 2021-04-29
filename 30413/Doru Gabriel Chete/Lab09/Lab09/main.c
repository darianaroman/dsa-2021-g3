#include <stdio.h>
#include <stdlib.h>
int array[100];

int maximum(int x, int y)
{
    return (x > y ) ? x : y;
}
int maximumSum(int left, int right)
{
    if(left == right)
    {
        return array[right];
    }
    int maximumLeft = -2000000;
    int sumLeft = 0;
    for(int i = (left + right) / 2; i >= left; i--)
    {
        sumLeft = sumLeft + array[i];
        maximumLeft = maximum(maximumLeft, sumLeft);
    }
    int maximumRight = -2000000;
    int sumRight = 0;
    for(int j = (left + right) / 2 + 1; j <= right; j++)
    {
        sumRight = sumRight + array[j];
        maximumRight = maximum(maximumRight, sumRight);
    }
    return maximum(maximumLeft + maximumRight, maximum(maximumSum(left, (left + right) / 2), maximumSum((left + right) / 2 + 1, right)));
}

int main(char argc, char **argv)
{
    FILE *fi;
    FILE *fo;
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "w");
    int i;
    int length;
    fscanf(fi, "%d", &length);
    for(i = 1; i <= length; i++)
    {
        fscanf(fi, "%d", &array[i]);
    }
    fprintf(fo, "The value of maximum subarray sum is: %d", maximumSum(1, length));
    fclose(fi);
    fclose(fo);
    return 0;
}
