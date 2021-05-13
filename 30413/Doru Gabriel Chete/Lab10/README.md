# Lab 10

> In this lab I learned more about dynamic programming and algorithm design, as well as more about the knapsack problem while solving problem 10.3.4
In order to solve the problem I built a function that computes the minimum number of operations (only addition and substraction) to reach a target
using only the elements of a vector that is a parameter of the function. The way it works is it starts traversing the vector from start to finish, 
and on the way it computes all possible addition/substraction operations. It is a recursive function, and on each run it calls itself in 3 ways:
firstly going to index i+1 and not adding or substracting anything, secondly going to index i+1 and adding the element with index i of the vector, 
and thirdly going to index i+1 and substracting the element with index i of the vector from the target. On each call, it checks if a minimum number
of operations has been found and it also checks if it reached the end of the vector and if so, returns.


