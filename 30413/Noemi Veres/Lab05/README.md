# Lab 5

/MANDATORY
> This problem was quite simple, I took the provided code and modified it if it was necessary.
> As the functions were already given, I only had to think about how to handle the given instructions.
> I read from file character-by-character in two characters: f and ch; 
> f - stands for function and ch - for give more exact information about what to do.
> depending on f and ch I made some switch cases to select the certain functions for each command

/EXTRA
> Given the expression in a file, I wanted to read that in a character string.
> From that on, I started to process the provided information
> I started from the end of the character string and extracted numbers/symbols until a space was met.
> If I extracted a number, I created a new node (I had to reverse the string) and pushed it to the stack.
> If it was a symbol, I created a new node again, I popped two elements from the stack assigning these
> to the left and right of the new node (connecting them), and pushed this new node to the stack.
> At the end I wanted to see if all went correctly using the preorder algorithm.

> I've tried to test my functions for the stack giving some certain examples and they seemed to work.
> I think that in the main on the else branch (for symbols) is where my program goes wrong, there the
> pop function doesn't seem to behave as I want. I've tried to see what's the top element of the stack
> using the peek function and this one doesn't always display that element which I logically think it would
> be at top.


