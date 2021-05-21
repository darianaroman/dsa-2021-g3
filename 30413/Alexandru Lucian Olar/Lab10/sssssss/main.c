#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


int matr(char string1[],char string2[],int lung1,int lung2)
{

    int matrix[lung1+1][lung2+1], i, j;
    for(i=0;i<=lung1;i++)
    {
        for(j=0;j<=lung2;j++)
        {
            if( i==0 ) matrix[i][j]= j;
               else
            if( j==0 ) matrix[i][j]= i;
               else
            if( string1[lung1-1]==string2[lung2-1] ) matrix[i][j]= matrix[i-1][j-1];

        }
    }
    return matrix[lung1][lung2];
}

int main()
{
    int matrix;
    char s1[25], s2[25];
    scanf("%c", s1);
    scanf("%c", s2);
    int lung1=strlen(s1), lung2=strlen(s2);
    matrix= matr(s1,s2,lung1,lung2);
    printf("%d",matrix);

    return 0;
}
