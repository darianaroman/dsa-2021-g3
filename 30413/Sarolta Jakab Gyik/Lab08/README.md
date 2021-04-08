# Lab 8

> With greedy algorithm the code prints the fractions to with the given fraction can be decomposed.
I used the gretest common divisor to simplify the fraction introduced by the user if possible. Then we swap the numerator and denominator.
Then we must find the least common multiple to subtract the new fraction from the given one, thus we get another part of the decomposition.
I tried to skip and have as few swappings as possible. So the numerator's and denominator's value do not switch back after every subtraction.
This is why we must list the value stored in the numerator at the end after the loop ends. That will store the value that should correspond to the denominator.


