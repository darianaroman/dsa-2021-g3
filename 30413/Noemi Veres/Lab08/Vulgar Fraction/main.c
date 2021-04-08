#include <stdio.h>
#include <stdlib.h>
FILE *openCheck (const char *path, const char *mode)
{
    FILE *pf = fopen(path,mode);
    if (pf == NULL)
    {
        puts("cannot open the file");
        exit(1);
    }
    return pf;
}
void egyptianFraction (int x, int y, FILE *pOut) /// prints the given vulgar fraction as a sum of fractions with the form 1/n
{
    if ((y % x) == 0)               /// we can write the fraction in the form 1/n
    {
        fprintf(pOut,"1/%d",y / x); /// n = y/x
        return;                     /// we can end the algorithm, return to main
    }
    int ceil = y / x + 1;           /// we are actually on the else branch, we calculate the ceil of the inverse fraction
    fprintf(pOut,"1/%d + ",ceil);   /// n = ceil
    egyptianFraction(ceil*x - y, ceil*y, pOut); /// we call recursively the function for the new numerator and denominator
}
int main(int argc, char *argv[])
{
    FILE *pIn = openCheck(argv[1], "r");
    FILE *pOut = openCheck(argv[2], "w");
    int x,y;
    fscanf(pIn,"%d",&x);
    fgetc(pIn);
    fscanf(pIn,"%d",&y);
    egyptianFraction(x,y,pOut);
    fclose(pIn);
    fclose(pOut);
    return 0;
}
