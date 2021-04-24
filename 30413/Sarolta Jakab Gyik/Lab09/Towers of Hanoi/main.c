/*The Towers of Hanoi. There are three pegs: A, B and C. Initially, peg A has on it a
number of disks, the largest at the bottom and the smallest at the top.
The task is to move the disks, one at a time, from peg to peg, never placing a
larger disk on top of a smaller one, ending with all disks on B.
I/O description. Input: a positive integer, the initial number of disks on peg A.
Output: consecutive configurations.
E.g. for 6 disks, the initial configuration would be:
A: 1 2 3 4 5 6
B:
C:
Here the numbers represent disk sizes, the lowest number indicating the smallest disk*/

#include <stdio.h>
#include <stdlib.h>

void towerOfHanoi(int n,char A, char B, char C)
{
    if(n == 1)
    {
        printf("Move disk 1 from rod %c to rod %c\n", A, B); ///the final disk
        return;
    }
    towerOfHanoi(n - 1, A, C, B); ///the auxiliary peg is B and the final peg is C
    printf("Move disk %d from rod %c to rod %c\n", n, A, B);
    towerOfHanoi(n - 1, C, B, A); ///move from peg C the disks to peg B-final step
}
int main()
{
    int nrPegs;
    printf("The number of disks:");
    scanf("%d", &nrPegs);
    towerOfHanoi(nrPegs, 'A', 'B', 'C'); ///the auxiliary peg is C, and the final one is B
    return 0;
}
