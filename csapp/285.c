/*
Given a floating-point format with a k-bit exponent and an n-bit fraction, write
formulas for the exponent E, the significand M, the fraction f , and the value V
for the quantities that follow. In addition, describe the bit representation.

A. The number 7.0
B. The largest odd integer that can be represented exactly
C. The reciprocal of the smallest positive normalized value
*/

// V = (-1)^s * M * 2^E

/* A
    // 7 = 0b111
    // 1.11 * 2^2 = 0b111
    // e = 2 + bias, m = 0b11. 
    // E = 2, M = 1.11, s = 0
*/

/* B
    // E = n + bias, e = n, m = 0b1...11, V = 1.11..1^n = 11111..1.0
*/

/* C
    // E = 0b0...01, e = 1 - bias, M = 0b0, V = 1 ^ 1 - bias
    // E = 0b11...101, e = bias - 1, M = 0b0, v = 1 ^ bias - 1
*/
