#include <stdio.h>
#include <stdlib.h>

#define INT_MAX  2147483646
#define INT_MIN -2147483646


int n,v[6000]; /// the array
int sp[6000]; /// partial sums

int main()
{
    int minim = INT_MAX;
    int maxim = INT_MIN;
    int maxpoz=1,minpoz = 1;

    FILE *f = fopen("ssm.txt", "r");

    /// read number of elements
    fscanf(f, "%d", &n);

    /// read elements of array
    for(int i=1; i<=n; i++)
        fscanf(f, "%d", &v[i]);

    sp[-1] = INT_MIN;

    for(int i=1; i<=n; i++)
    {
        sp[i] = sp[i-1] + v[i]; /// calculate the sum till the current element

        /// calculate the minim
        if(sp[i-1] < minim){
            minim = sp[i-1];
        }
        /// if subtracting minim from current sum is bigger then max, we have new max and set the position of the max element
        if(sp[i] - minim > maxim){
            maxim = sp[i] - minim ;
            maxpoz = i;
        }
    }

    int i = maxpoz;
    int sum = v[maxpoz];
    /// find minim
    while (sum != maxim)
    {
        i--;
        sum += v[i];
    }

    int mini = i;
    /// treats special case
    while(v[mini-1] == 0)
        mini = i--;

    ///print results
    printf("%d\n", maxim);

    for(int i = mini; i <= maxpoz; i++)
        printf("%d ", v[i]);


    return 0;
}
