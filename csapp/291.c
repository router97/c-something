/*
Around 250 B.C., the Greek mathematician Archimedes proved that 223/71 < π < 22/7.
Had he had access to a computer and the standard library <math.h>, he would have
been able to determine that the single-precision floating-point approximation of
π has the hexadecimal representation 0x40490FDB. Of course, all of these are just
approximations, since π is not rational.

A. What is the fractional binary number denoted by this floating-point value?
B. What is the fractional binary representation of 22/7? Hint: See Problem 2.83.
C. At what bit position (relative to the binary point) do these two approximations to π diverge?
*/


/* A
(1 + 1/2) * 2^1 == 3

0x40490FDB
0100 0000 0100 1001 0000 1111 1101 1011
0 10000000 10010010000111111011011
sign = 0, e = 1, m = 0b1.10010010000111111011011
0b1.10010010000111111011011 * 2^1 = 0b11.0010010000111111011011
*/


/* B
3 + 1/7 = 11.  0   0   1   0    0    1  ...
           3  1/2 1/4 1/8 1/16 1/32 1/64
*/


/* C
0b11.0010010000111111011011
0b11.001001001001001001...
             ^
*/