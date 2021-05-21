# Lab 09

> Learned about divide et impera. 
> Coded together merge sort.
> Solved the mandatory problem.
*Extra problem(Tower of Hanoi)
For this problem I used the divide et impera method.
In order to solve the big problem we need to solve smaller problems first.
To move n discs from peg A to peg C we need to move n-1 discs from peg A to peg B(using C), move 1 disc from peg A to peg C and move n-1 discs from peg B to peg C(using A). We can easily observe the reccursive manner of this problem.
In order to print the elements in the way presented in the problem I represented each peg as a stack and implemened the necessary operations: pop, push, createStackNode, createStack, printStack. I also used a function called moveDisc to move a disc between 2 pegs when needed.

Note: I forgot to include a function to purge the stacks.


