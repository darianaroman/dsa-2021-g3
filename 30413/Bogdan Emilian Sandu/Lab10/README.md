# Lab 10

> Discussed about dynamic programming and heuristics.
> Solved the problem with min path cost.

------------------
> Homework problem:
Used Bezout identity and coefficients in order to solve the problem.
Bezout Identity: given 2 numbers A and B and their GCD(greatest common divisor) we have
A * X + B * Y = GCD where X and Y are Bezout's coefficients.
NOTATION : |A - B| = C;

Test to see if problem is solvable:

If the GCD of any 2 given numbers in the array divides C then according to Bezout's Identity and coefficients we can obtain the number C.
If the test is negative the result will be -1.

Algorithm:

1. Using Bezout's identity and coefficients I calculated the numbers of operations needed to obtain C (MIN).
I used this number as a way to stop the algorithm which  uses a BRUTE FORCE approach (see CODE BRUTE).
2. I created an array(DP) which contains the number of operations to obtain any number from 
1 to max(|A-B| and biggest element in the array).
3. For every element in the array, DP[element] = 1; (min nr of steps to obtain it is 1).
4. Traverse DP and calculate for the rest the minimum nr of steps to obtain the number representing its index.
5. For every element in DP which needs to be calculated use the following formula:
If its value its already 1 skip it.(no need to calculate).
Else choose between the minimum of ( DP[abs(C-array[0])],DP[abs(C-array[1])],...,DP[abs(C-array[n-1])] )= MIN.
If all of them are already calculated then DP[currentPos] = MIN + 1; (we add 1 to include the actual operation).
For every value which is not already calculated we recursively calculate it and in the same time we track the nr of operations. If the number of operations exceeds MIN we stop the reccursion. Either 2 things happened: the nr of operations exceeded MIN so we dont need to do more work or it will loop infinitely.
6. We return the value in DP[C]. 

CODE BRUTE:

NOTE: |A-B| = C so if we use the absolute value between the 2 numbers. We need to make the difference between the 2 (C) to be 0. With this method we can count any operation as a substraction and we update C as C = |C - element|.

int pasiBezut = MIN (calculated using Bezout)
void minOp(int C,int *vector,int length,int nrMin,int *pasiBezut){
    if(nrMin >= *pasiBezut) return;
    if (C == 0) {
        if(nrMin < *pasiBezut)
            *pasiBezut = nrMin;
        return;
    }
    nrMin++;
    for(int i =0; i < length; i++) {
        minOp(abs(C - vector[i]), vector, length, nrMin, pasiBezut);
    }
}

