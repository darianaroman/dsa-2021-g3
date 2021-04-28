#include <stdio.h>

int maxNr(int a, int b, int c) { // function to find which is the biggest out of 3 numbers
    if (a > b && a > c) {
        return a;
    }
    else if (b > c) {
        return b;
    }
    return c;
}

int maxSumArray(int array[], int l, int r) {
    if (l == r) { // if the array introduced contains a single element, return that element
        return array[l];
    }

    int i;
    int m = (l + r) / 2; // middle of the array
    int lsum = array[m], rsum = array[m + 1]; // initialize the sum to the left and right of the middle point with their first elements

    int sum = lsum;
    for (i = m - 1; i >= l; i--) { // find the biggest sum of the elements on the left with the right edge in the midpoint
        sum = sum + array[i];
        if (sum > lsum) {
            lsum = sum;
        }
    }

    sum = rsum;
    for (i = m + 2; i <= r; i++) { // find the biggest sum of the elements on the right with the left edge in the midpoint
        sum = sum + array[i];
        if (sum > rsum) {
            rsum = sum;
        }
    }

    return maxNr(maxNr(lsum, rsum, lsum + rsum), maxSumArray(array, l, m), maxSumArray(array, m + 1, r));
}

int main(int argc, char* argv[]) {
    int array[100], i = 0;

    FILE* in = fopen(argv[1], "r"); // input file
    if (in == NULL) {
        printf("Input file not found or not introduced!");
        return 1;
    }

    FILE* out = fopen(argv[2], "w"); // output file
    if (out == NULL) {
        printf("Output file not introduced!");
        return 2;
    }

    while (fscanf(in,"%d", array + i) != EOF) { // saving the numbers from the input fine in an array
        i++;
    }
    fprintf(out,"The value of the maximum subarray sum is %d.", maxSumArray(array,0,i)); // putting the sum into the output file
    fclose(in);
    fclose(out);
    printf("OK");
    return 0;
}