#include <stdio.h>
#include <limits.h>

// array to store the minimum number of operation used to obtain a certain number from 0
// if the number of operations is equal to INT_MAX, then the number can't be obtained
int nrOperMin[1000];

// the function to generate the array of minimum operations for numbers from 0 to max
void minOper(int v[], int len, int max) {
    int i, j, aux;
    int ok = 0; // variable used to check if the function changed anything in the number of operations array

    // we find the minimum number of operations by only addition
    for (i = 1; i <= max; i++) { // we generate the number of operations for each number smaller than the max
        for (j = 0; j < len; j++) {
            if (v[j] <= i) { // we use all values smaller than i
                aux = nrOperMin[i - v[j]]; // i - v[j] represents the number of coins for which by adding v[j], we obtain i
                // if aux wasn't generated before and aux + 1 (nr of operations incremented by 1) is smaller than the number of operations used to obtain i
                if (aux != INT_MAX && aux + 1 < nrOperMin[i]) {
                    nrOperMin[i] = aux + 1; // then the number of operations used to obtain i is aux + 1
                    ok = 1; // this value shows that the array of number of operations changed
                }
            }
        }
    }

    // now we find the minimum number of operations by only subtraction
    for (i = 1; i <= max; i++) {
        // we generate the number of operations for each number smaller than the max
        for (j = i; j <= max; j++) {
            // we use the numbers bigger than i
            if (nrOperMin[j] != INT_MAX && nrOperMin[j - i] != INT_MAX) { // if the number of operations are valid
                aux = nrOperMin[j] + nrOperMin[j - i]; // complementary numbers, j + (j - i) = i for any j bigger than i
                if (aux < nrOperMin[i]) { // we find the minimum number of operations between all complementary numbers
                    nrOperMin[i] = aux;
                    ok = 1; // this value shows that the array of number of operations changed
                }
            }
        }
    }
    if (ok == 1) { // if the array of number of operations changed, we call the function again until it doesn't change anymore
        minOper(v, len, max);
    }
}

int main() {
    int nr, i, len, max;
    int v[100];

    nrOperMin[0] = 0; // the number 0 is obtained by 0 operations
    for (i = 1; i < 1000; i++) { // initialize the other numbers with INT_MAX
        nrOperMin[i] = INT_MAX;
    }

    FILE *in = fopen("input.txt", "r"); // input file
    if (in == NULL) {
        printf("Input file not found or not introduced!");
        return 1;
    }
    FILE *out = fopen("output.txt", "w"); // output file
    if (out == NULL) {
        printf("Output file not introduced!");
        return 2;
    }

    fscanf(in, "%d", &nr); // obtaining the first number
    fscanf(in, "%d", &i); // obtaining the second number
    nr = nr - i;
    if (nr < 0) { // finding the module between the 2
        nr = nr * (-1);
    }
    // the problem is reduced to how many additions and subtractions are needed to find a certain number (the module found before)

    // max represents for how many numbers do we need to calculate the number of operations
    // max is equal to the maximum out of the module and the biggest number from the vector of values
    max = nr;
    for (i = 0; fscanf(in, "%d", v + i) != EOF; i++) { // saving the values in a vector
        if (max < v[i]) {
            max = v[i];
        }
    }
    len = i; // how many elements are in the vector
    minOper(v, len, max); // the function to generate the array of minimum operations for numbers from 0 to max

    if (nrOperMin[nr] == INT_MAX) { // if the number of operations used to find the module is equal to INT_MAX, then the module can't be obtained
        fprintf(out, "0");
    }
    else { // otherwise, nrOperMin[nr] is the minimum number of operations used to find the module
        fprintf(out, "%d", nrOperMin[nr]);
    }
    return 0;
}
