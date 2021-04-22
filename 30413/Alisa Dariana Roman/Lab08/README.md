# Lab 8

> we were introduced to greedy algorithms ex: prim's alg, minimum number of banknotes to pay a sum, vulgar fractions

algorithm for vulgar fractions:
while up > 1:
	- rounded = ceil(down/up)
	- output 1/rounded
	- subtract 1/rounded from up/down
	- simplify the new fraction using the function cmmdc (returns greatest common divisor)
output 1/down , the last fraction