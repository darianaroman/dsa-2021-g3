# Lab 10

> I solved the Minimum path problem as we discussed at the lab, by creating a matrix with the minimum cost for each cell.
> The weight for the starting point was given, I had to fill the 1 row and coloumn, and then the other cells by the following method:
> minimum for a certain cell = minimum between (left, up and left, left) + weight

*Add and Substract
> In this problem I had to calculate dynamically the minimum number of opeartions from which we can obtain one number from the other using the given vector.
> Actually, we had to determine in how many steps can we reach the absolute value of the two numbers. 
> From a mathematical point of view, I had to find solutions to a Diophantine equation such that the sum of the solutions is minimal.
> In the problem that sum was required.
> To find that sum, we should think first how could we obtain a minimum number of steps for a number X.
> The minimum number of steps for X can be obtained recursively as follows:
> 1 + the minimum of the minimum number of steps required for each X - v[i], where v[i] is an element from the given vector
> As we have to solve the problem dynamically, we should construct a new vector which is initialized with 0s
> We start from index 0 and add the numbers from the given vector to obtain the indexes which can be reached within 1 step.
> Then we want to find the indexes which can be obatined adding one step for the already reached elements, by adding and also substracting the numbers.
> So with each step we'll find how far we can go using the numbers from the given vector.
> If we reach in a certain number of steps the last element of our new array, we can stop and print this number of steps which is minimum.
> If from a certain number of steps we can only go to indexes which were already visitedd, we can stop, as this means we cannot obtain number X.


