# Lab 9

> For the mandatory assignment: the divideEtImpera function divides the array in
2 subarrays. We find the maximum for both of the subarrays. Then the greater maximum gets
stored in a variable maxArrays. We should also check if in the middle there is a
subarrays with elements from both parts and its maximum is greater then the previous
maxArrays calculated. So to do this we use ind1 and ind2 variables that store the
indeces of the 2 maximum subarrays. Ind1 is the last index of the maximum subarray
from the first half, ind2 is the first index of the maximum subarrays from the second 
half + mid, so we get the actual index of the element in the original array.
We add all the elements to midArray variable that are in between the 2 indeces. We also
add the 2 maximums. At the end we return the greater value, the midArray calculated or
the maxArray.
 For the extra credit problem, the tower of Hanoi is solved with recursion.
The stopping condition is when we only have to place 1 last disk to the top of the final
peg. Until we reach this point the function calls itself decrementing the number of disks
at each step and also changing the destination peg and the auxiliary peg.

