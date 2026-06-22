/*
Consider the following two 9-bit floating-point representations based on the IEEE
floating-point format.

1. Format A
There is 1 sign bit.
There are k = 5 exponent bits. The exponent bias is 15.
There are n = 3 fraction bits.

2. Format B
There is 1 sign bit.
There are k = 4 exponent bits. The exponent bias is 7.
There are n = 4 fraction bits.

In the following table, you are given some bit patterns in format A, and your
task is to convert them to the closest value in format B. If rounding is necessary
you should round toward +∞. In addition, give the values of numbers given by
the format A and format B bit patterns. Give these as whole numbers (e.g., 17) or
as fractions (e.g., 17/64 or 17/26).
*/


/*
| Bits        | Value    | Bits        | Value    |
|-------------|----------|-------------|----------|
| 1 01111 001 |  -9/8    | 1 0111 0010 |  -9/8    |
| 0 10110 011 |   176    | 0 1110 0110 |   176    |
| 1 00111 010 | -5/1024  | 1 0000 0100 | -4/1024  |
| 0 00000 111 | 7/131072 | 0 0000 0001 |  1/1024  |
| 1 11100 000 |  -8192   | 1 1110 1111 |  -248    |
| 0 10111 100 |   384    | 0 1110 1111 |   248    |
*/


/* 22222222222222222222222222
sign = 0, e = 7, m = 1 + 1/4 + 1/8
0 10110 011
(1 + 3/8) * 2^7 = 11/8 * 2^7 = 11 * 2^-3 * 2^7 = 11 * 2^4

--

sign = 0, e = 7, m = 1 + 1/4 + 1/8
0 1110 0110
SAME
*/


/* 333333333333333333333333333
sign = 1, e = -8, m = 1 + 1/4
1 00111 010
(1 + 1/4) * 2^-8 = 5/4 * 2^-8 = 5 * 2^-2 * 2^-8 = 5 * 2^-10
5/4 * 2^-8 = 5/4 * 1/256 = 5/1024
-5/1024

--

sign = 1, e = -6, m = 0 + 1/4
1 0000 0100
1/4 * 2^-6 = 1/4 * 1/64 = 1/256 = 4/1024
-4/1024
*/


/* 44444444444444444444444444444444
sign = 0, e = -14, m = 1/2 + 1/4 + 1/8 = 7/8
0 00000 111
7/8 * 2^-14 = 7 * 2^-3 * 2^-14 = 7 * 2^-17

--

sign = 0, e = -6, m = 1/16
0 0000 0001
1/16 * 2^-6 = 2^-4 * 2^-6 = 2^-10
*/


/* 5555555555555555555555555555555555
sign = 1, e = 13, m = 1
1 11100 000
2^13 * (-1) = -8192

--

sign = 1, e = 7, m = 1 + 1/2 + 1/4 + 1/8 + 1/16 = 1 + 15/16 = 31/16
1 1110 1111
31/16 * 2^7 * (-1) = 31 * 2^-4 * 2^7 * (-1) = 31 * 2^3 * (-1) = -248
*/


/* 66666666666666666666666666666666666
sign = 0, e = 8, m = 1 + 1/2 = 3/2
0 10111 100
3/2 * 2^8 = 3 * 2^-1 * 2^8 = 3 * 2^7 = 384

--

sign = 0, e = 7, m = 1 + 1/2 + 1/4 + 1/8 + 1/16 = 1 + 15/16 = 31/16
0 1110 1111
31/16 * 2^7 = 31 * 2^-4 * 2^7 = 31 * 2^3 = 248
*/
