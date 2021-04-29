#include <stdio.h>
#include <math.h>

int convert2nr(char in[]) { // function to convert the number from the string into an integer
    int nr = 0, i;
    for (i = 0; in[i] >= '0' && in[i] <= '9'; i++) {
        nr = nr * 10 + (int)(in[i] - '0');
    }
    return nr;
}

int main() {
    int denom, unitdenom, i;
    double numer;
    char in[50];

    printf("In: "); // as input, we take a fraction written like in this example: 5/8
    scanf("%s", in);

    numer = convert2nr(in); // we save the number before "/" into numer

    for (i = 0; in[i] != '/'; i++);
    denom = convert2nr(in + i + 1); // we save the number after "/" into denom

    printf("Out: ");
    while (numer > 0.00000001) { // we will use the Greedy algorithm for Egyptian Fractions until the numerator will be so small we can say it's zero
        unitdenom = ceil((double) denom / numer); // we find the denominator for the next element in the sum
        numer = numer - (double) denom / (double) unitdenom; // we subtract the number from the sum that we found from the numerator

        printf("1/%d ", unitdenom); // printing the element from the sum
        if (numer > 0.00001) {
            printf("+ "); // if the element is not the last, print a plus
        }
    }
    return 0;
}
