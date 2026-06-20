/*
Consider numbers having a binary representation consisting of an infinite string
of the form 0.y y y y y y ... , where y is a k-bit sequence. For example, the binary
representation of 1/3 is 0.01010101 ... (y = 01), while the 
representation of 1/5 is 0.001100110011 ... (y = 0011).

A. Let Y = B2Uk(y), that is, the number having binary representation y. Give
a formula in terms of Y and k for the value represented by the infinite string.
Hint: Consider the effect of shifting the binary point k positions to the right.

B. What is the numeric value of the string for the following values of y?
(a) 101
(b) 0110
(c) 010011
*/

// x = 0 . y y y y y ...
// x * 2^k  = y . y y y y y ...
// x * 2^k - x = Y


// 5 = x * 2^3 - x
// 5 = 7x
// x = 5/7

// 6 = x * 2^4 - x
// 6 = 15x
// x = 6/15
// x = 2/5

// 19 = x * 2^6 - x
// 19 = 63x
// x = 19/63
