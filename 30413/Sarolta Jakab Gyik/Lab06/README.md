# Lab 6

> The hash function that I used is to add the ascii values of the characters except the space character (because in the full names of the student we will have
spaces). And then it counts mod 25 because there are 25 letter characters in total. So the nr of the hash table is gonna be B = 25.
Then we read the first character of every line. If we need to insert we read the name from the file. Create a new node, fill the node with the fillNode
function, and insert it in the table. If we have to delete, then we do a searchByKey to know if the node is in the bucketList or not at all.
If we need to find a certain node then after reading the name from the file the searchByKey function returns a pointer to a node. If that pointer is Null
then the node is not in the table. Otherwise, p->new, that points to the index of the place where it is found, gets printed.


