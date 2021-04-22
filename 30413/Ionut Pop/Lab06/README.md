# Lab 6

problem 6.3.1:
	-the hash function that I used return the sum modulo N of the ascii values of the characters, where N is the number
												      of rows in the table 
	-this hash function ensures that each new elemen will be inserted on a row with index <= N, and so if there is a
	 collision between two nodes the new node is placed in the same row, with the previews node in row pointing to it
