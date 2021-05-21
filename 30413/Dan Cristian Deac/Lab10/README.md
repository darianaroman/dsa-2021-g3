# Lab 10

> Dynamic Programming

I tried to find an optimal solution for this problem but the issue is i couldnt find a 100% working algorithm. for the cases in which there are 1 and 2 moves the algorithm works but when there are more then 3 i have a "not so good" solution. 

That solution works like this: look for the closest number to NUM = A - B ( if A > B). then look for the closest number to [NUM - closest number to NUM found in V]. untill i found one that fits the difference and got the solution. this is a greedy algorithm and it doesnt work taking into consideration calculations that can be made with other numbers.




