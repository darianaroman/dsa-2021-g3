#include <stdio.h>

int m[100][100], minP[100][100];

int min3Nr(int a, int b, int c) { // function used to calculate the minimum out of 3 numbers
    if (a < b && a < c) {
        return a;
    }
    else if (b < c) {
        return b;
    }
    return c;
}

void minimumPath(int l, int c) { // function used to generate the minimum path matrix
    int i, j; // index variables

    minP[0][0] = m[0][0]; // firstly, the first element in the resulted matrix has the same value as the first element in the primary matrix
    for (i = 1; i < c; i++) { // secondly, we calculate the weight of the elements on the top edge of the matrix
        minP[0][i] = minP[0][i - 1] + m[0][i]; // each one has the value of the one behind it + the weight of it's position from the primary matrix
    }
    for (i = 1; i < l; i++) { // thirdly, we calculate the weight of the elements on the left edge of the matrix
        minP[i][0] = minP[i - 1][0] + m[i][0]; // each one has the value of the one behind it + the weight of it's position from the primary matrix
    }
    for (i = 1; i < l; i++) {
        for (j = 1; j < c; j++) {
            minP[i][j] = min3Nr(minP[i - 1][j], minP[i][j - 1], minP[i - 1][j - 1]) + m[i][j];
        }
    }
    // lastly, each other element has as the value the minimum of the 3 proceeding elements + it's weight from the primary matrix
}

int main() {
    int l, c; // variables representing the number of lines and columns of the matrix
    int i, j; // index variables

    // the input will contain on the first line the number of lines and columns of the matrix, and starting from the next line, it will be the matrix
    FILE* in = fopen("input.txt", "r"); // input file
    if (in == NULL) {
        printf("Input file not found or not introduced!");
        return 1;
    }

    FILE* out = fopen("output.txt", "w"); // output file
    if (out == NULL) {
        printf("Output file not introduced!");
        return 2;
    }

    fscanf(in, "%d", &l);
    fscanf(in, "%d", &c);
    // saving the number of lines and columns

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            fscanf(in, "%d", &m[i][j]);
        }
    }
    // saving the matrix

    minimumPath(l, c); // generating the minimum path matrix
    fprintf(out, "The resulted minimum path matrix is:\n"); // the output
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            fprintf(out, "%d ", minP[i][j]);
        }
        fprintf(out, "\n");
    }
    fprintf(out, "And the minimum weight of the path from the first element (0,0) to the last element (%d,%d) is %d.", l, c, minP[l - 1][c - 1]);
    fclose(in);
    fclose(out);
    return 0;
}
