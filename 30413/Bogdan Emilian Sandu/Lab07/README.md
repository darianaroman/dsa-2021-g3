# Lab 07

>Learned about graphs, how to implement them and how to traverse them using depth first search and breadth first search.
>Solved the extra assignment. I think I can do it faster but I didn't have time.
>Method used for solving extra:
Notes: 
 I used a singly linked list instead of a dinamically allocated array for the order of robots just to remind myself some notions.
 Also we disscussed at the lab that we need to use oriented graphs in order to solve this problem.
1. I used the input that I was given to create a adjacency matrix and also created an array(!) which contained all the pairs of robots given(will come in use later).
2. I created a singly linked list containing all the distinct vertices (not sorted yet).
3. Observed that the smaller the inner degree of a vertex the faster the robot and tried sorting the linked list using a bubble sort by this criteria.
4. Later on I found out that the inner degree is not the only thing that needs to be taken into account when sorting, I also had to look at the given list of the robots ( here (!) comes into play). If the inner degree of 2 vertices is equal but they appear in the array skip.

Example:
Input:     Adj matrix
			   1 2 3 4 5
4			
1 2			1  0 1 1 0 0
1 3			2  0 0 0 0 0
4 1			3  0 0 0 0 0
4 5			4  1 0 0 0 1
			5  0 0 0 0 0

We notice that all the vertices have the same inner degree so the first method would't work. We must use the input given. If 2 vertices have the same inner degree and they apper in the correct order in our array we skip, otherwise we invert them.

Ex. 1 and 2 have the same inner degree but if we swap them the sorting is wrong. 