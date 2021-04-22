#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmmdc (int x, int y)
{
    if (y == 0) {
        return x;
    }
    return cmmdc(y, x%y);
}

int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    int up, down;

    fscanf(fileI, "%d/%d", &up, &down);

    fprintf(fileO, "up = %d\n", up);
    fprintf(fileO, "down = %d\n", down);

    double aux;
    int rounded, divisor;

    while (up > 1) {
        aux = (double) down/up;

        rounded = ceil(aux);        /// keep 1 / rounded
        fprintf(fileO, "1/%d + ", rounded);

        up = up * rounded - down;   /// subtracting 1/rounded from up/down
        down = down * rounded;
        divisor = cmmdc(up, down);

        up = up / divisor;          /// simplifying the fraction
        down = down / divisor;
    }
    fprintf(fileO, "1/%d", down);

    return 0;
}
