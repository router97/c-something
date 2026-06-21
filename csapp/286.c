/*
Intel-compatible processors also support an “extended-precision” floating-point
format with an 80-bit word divided into a sign bit, k = 15 exponent bits, a single
integer bit, and n = 63 fraction bits. The integer bit is an explicit copy of the
implied bit in the IEEE floating-point representation. That is, it equals 1 for
normalized values and 0 for denormalized values. Fill in the following table giving
the approximate values of some “interesting” numbers in this format:
Extended precision
Description Value Decimal
Smallest positive denormalized
Smallest positive normalized
Largest normalized
This format can be used in C programs compiled for Intel-compatible machines by declaring the data to be of type long double. 
However, it forces the compiler to generate code based on the legacy 8087 floating-point instructions.
The resulting program will most likely run much slower than would be the case
for data type float or double.
*/

// Smallest positive denormalized
// Value -> sign=0, e=1-bias, int=0, f=0b0...01
// decimal -> 0.00.(59 0s)..01 * 2 ^ (-16382)

// Smallest positive normalized
// Value -> sign=0, e=1-bias, int=1, f=0
// decimal -> 1.00...(59 0s)..00 * 2 ^ (-16382)

// Largest normalized
// Value -> sign=0, e=(2^15)- 2 - bias, int=1, f=0b11...11
// decimal -> 1.11...(59 1s)..11 * 2 ^ 16,383

// bias = 16,383
