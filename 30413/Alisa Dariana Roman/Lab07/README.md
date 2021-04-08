# Lab 7

> we learned to implement graphs in c (using adjacency matrix/adjacency list) and also how to traverse them using bfs and dfs

extra:
if robot a is faster than robot b => arc (a, b)

we need to find a path that contains all nodes such that if arc (a, b) exists (a is faster than b) then
a will come before b in this path

algorithm: (in linear time I think)
- graph implemented with adjacency list
- intialize queue with nodes that have in degree 0
- repeat until queue empty:
	- delete first node of queue, print it
	- go through adjList of deleted node and do inDegree-- for every node in this list
	- add to queue nodes that now have inDegree 0