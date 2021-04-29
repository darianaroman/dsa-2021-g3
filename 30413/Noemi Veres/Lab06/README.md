# Lab 6

> I used a hash function with mod 10, but this number can be modified.
> To transform a string to an integer, I calculated the sum of the ASCII codes of each character
> To SEARCH for a certain name, I had to calculate the hash code for the name and than search on that line of the bucket table
> INSERTing a new name was a bit more complex, if there was no other element with the same hash code, I  only had to put there the new name
> If there was already an element at that point, I had to insert the new element at the end of that line, which is actually a singly linked list
> By DELETION there were more possibilities: if the name was the only one on that position, then we only had to reset the table on that position.
> If the name was the second and also the last element in the list, I only had to redo the chaining, so the first element is pointing to nothing.
> If there were more than to elements in the list, I worked with two pointers, so after I found the element to be deleted, I also knew which was
> its previous element and from that on, I chained the previous and next element together, and freed the certain element.
> By LISTING I had print the lines of the bucket table which were not zero. The end of a line was reached, when I encountered NULL.


