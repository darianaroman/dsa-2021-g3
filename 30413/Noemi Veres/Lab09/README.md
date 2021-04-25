# Lab 9

> To obtain the value of maximal subarray sum, I wanted to divide the problem in more parts. As we discussed about merge sort at laboratory,
> I wanted to find the value of maximal subarray sum on the left and on the right of the array and so on. But this was not enough, because
> a subarray could also pass through the midpoint of the array, so I also had to handle this situation. For this, I had to find the maximal subarray
> starting with the midpoint to the left and then find the maximum after the midpoint.
> To find the maximum of 3 integers, I divided the problem in two parts, so first I calculated the maximum of the first 2 integers 
> and after that the maximum of the maximum and the last integer.

# Extra - Towers of Hanoi
> I solved this recursively, using the Divide et impera method.
> To move n disks from peg A to peg B I used the following algorithm:
> move n-1 disks from A to C
> move the last disks from A to B
> move n-1 disks from C to B
> To implement the problem, I used stacks, because this game has the idea that you can only remove a peg if it's on the top.
> I also had to write a function for printing the content of the pegs for which another function was needed, by which I decided the order in which
> I had to print the rods (as the auxiliary peg is not always the one with letter C).


