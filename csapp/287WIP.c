/*
The 2008 version of the IEEE floating-point standard, named IEEE 754-2008,
includes a 16-bit “half-precision” floating-point format. It was originally devised
by computer graphics companies for storing data in which a higher dynamic range
is required than can be achieved with 16-bit integers. 

This format has 
1 sign bit, 
5 exponent bits (k = 5), 
and 10 fraction bits (n = 10). 
The exponent bias is 2^(5-1) - 1 = 15
*/

/*

https://www.tablesgenerator.com/markdown_tables

| Description          | Hex  |   M       | E  | V            | D                          |
|----------------------|------|-----------|----|--------------|----------------------------|
| -0                   | 8000 | 0         | 0  | 0            | -0.0                       |
| Smallest value > 2   | 4001 | 1/1024    | 16 | 1025*2^-9    | 2.001953125                | 
| 512                  | 6000 | 0         | 9  | 512          | 512.0                      |
| Largest denormalized | 03FF | 1023/1024 | 0  | 1023 * 2^-24 | 0.000060975551605224609375 |
| -Infinity            | FC00 | -         | -  | -Infinity    | -Infinity                  |
| 0x3BB0               | 3BB0 | 59/64     | -1 | 123 * 2^-7   | 0.9609375                  |

Hex: The four hexadecimal digits describing the encoded form.

M: The value of the significand. This should be a number of the form x or x/y ,
where x is an integer and y is an integral power of 2. Examples include 0,
67/64 , and 1/256 .

E: The integer value of the exponent.

V : The numeric value represented. Use the notation x or x × 2^z, where x and
z are integers.

D: The (possibly approximate) numerical value, as is printed using the %f
formatting specification of printf.
*/

// -0: sign=1, exp=0, m=0

// Smallest value > 2 
// 0 10000 0000000001 | 0100 0000 0000 0001 | 4001
// sign=0, exp=16-15=2, m=1/1024
// (1 + 1/1024) * 2^1 = 2.001953125
// 1025/1024 * 2^1 = 1025 * 2^-10 * 2^1 = 1025 * 2^-9


// 512: sign = 0, exp = 9, m = 0b0
// 1.0 * 2^9 = 1.0 * 512 = 512
// 9 + 15 = 24
// 0 11000 0000000000
// 0110 0000 0000 0000  | 6000

// largest denormalized
// 0 00000 1111111111 | 0000 0011 1111 1111 | 03FF
// sign=0, exp=0, m=1023/1024
// 1023/1024 * 2^-14 = 0.000060975551605224609375
// 1023 * 2^-10 * 2^-14 = 1023 * 2^-24

// -Infinity: 1 11111 0000000000 | FC00

// 3BB0 | 0011 1011 1011 0000 | 0 01110 1110110000
// sign=0, exp=14-15=-1, m=59/64
// (1 + 59/64) * 2^-1 = 123/64 * 2^-1 = 123 * 2^-7 = 
