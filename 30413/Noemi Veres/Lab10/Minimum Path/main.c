#include <stdio.h>
#include <stdlib.h>
int min2 (int a, int b)
{
    if (a < b) return a;
    return b;
}
int min3 (int a, int b, int c)
{
    return min2(min2(a,b),c);
}
int minPath (int mat[4][7])
{
    int min_path[4][7];
    min_path[0][0] = mat[0][0]; /// starting point
    for (int j = 1; j < 7; j++) /// first row
    min_path[0][j] = min_path[0][j-1] + mat[0][j]; /// add the weight to the minweight of the previous element (from left)
    for (int i = 1; i < 4; i++) /// first coloumn
    min_path[i][0] = min_path[i-1][0] + mat[i][0]; /// add the weight to the minweight of the element above
    for (int i = 1; i < 4; i++)
        for (int j = 1; j < 7; j++)
        min_path[i][j] = min3(min_path[i][j-1],min_path[i-1][j-1],min_path[i-1][j]) + mat[i][j];
        /// minimum between left, up and left, left + weight
    return min_path[3][6];
}
int main(){
    int mat[4][7] = { {1, 2, 3, 6, 9, 2, 4},
                        {5, 3, 1, 7, 3, 9, 4},
                        {13, 2, 4, 1, 1, 1, 1},
                        {5, 9, 7, 8, 10, 6, 4}};
    printf("%d",minPath(mat)); /// 11 is displayed
    return 0;
}
