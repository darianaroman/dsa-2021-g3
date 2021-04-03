# Lab 7

> Given the hint that I have to work with a directed graph, I wanted to mark the present edges in an adjacency matrix.
> So first of all I had to get the dimension of this matrix: I went through the file and searched for the maximal element.
> (Then I put back the file pointer to the beginning of the file.)
> I initialized the matrix with 0s.
> I went through the file again, read the relations and put a 1 in the matrix when a relation appeared.
> Now I had to decide how to get an order between all the robots. 
> First I thought about BFS and DFS, but I realized that they I need another, but similar algorithm.
> I took a "degree" vector, where I stored the indegree of each vertex(robot), adding the elements in each row.
> I chose a while loop for getting the order of the elements.
> If the indegree of a vertex is 0, it means that we can prepare it for printing out because all the faster robots are already written in the output file.
> In each step, we had to decrease the degree for all the vertices to which the printed vertex is directed.
> I also decreased the degree of the vertex which would be printed, so it got the value -1 and I knew that it could be written to the file.
> Then I set its value to -2, by which I marked that it was already printed out.
> When all the vertices were printed, the while loop would stop.

