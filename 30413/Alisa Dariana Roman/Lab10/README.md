# Lab 10

We discussed about dynamic programming, learned to optimize Fibonacci recursive algorithm and talked about minimum path algorithm

algorithm for mandatory problem:
- to get from a to b we need to find minimum number of operations to obtain
  x = abs(b - a) using the elements of the vector

- I initialized an array from 0 to x + 1 where I save the minimum number
  of operations needed for each number in that range: starting from 1 to x

- dp[0] is initialized as 0 in order to start the algorithm
