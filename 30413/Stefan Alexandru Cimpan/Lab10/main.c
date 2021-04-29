#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include<limits.h>

int min(int a, int b, int c);
int mcost(int cost[3][3], int m, int n)
{
     int i, j;
     int col[3][3];

     col[0][0] = cost[0][0];

     for (i=1;i<=m;i++)
     {
         col[i][0]=col[i-1][0]+cost[i][0];
     }

     for (j=1;j<=n;j++)
     {
         col[0][j]=col[0][j-1]+cost[0][j];
     }

     for (i=1;i<=m;i++)
     {
            for(j=1;j<=n;j++)
            {
            col[i][j]=min(col[i-1][j-1],
            col[i-1][j],
            col[i][j-1])+cost[i][j];
            }

     }
     return col[m][n];
}
int min(int a, int b, int c)
{

   if (a<b)
      return (a<c)? a:c;
   else
      return (b<c)? b:c;

}
int main()
{
   int cost[3][3] = { {1, 2, 3}, {4, 8, 2}, {1, 5, 3} };
   printf("Costul de parcurgere al matricei este: %d \n\n\n\n", mcost(cost, 2, 2));
   return 0;
}
