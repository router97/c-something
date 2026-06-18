/*
Return 1 when x contains an odd number of 1s; 0 otherwise.
Assume w=32

Your function should follow the bit-level integer coding rules (page 164),
except that you may assume that data type int has w = 32 bits.

Your code should contain a total of at most 12 arithmetic, bitwise, and logical
operations.
*/

/* Numbers with even 1s
0
3
5
6
9
10
12
15
17
18
20
23
24
27
29
30
33
34
36
39
40
43
45
46
48
51
53
54
57
58
60
63
65
66
68
71
72
75
77
78
80
83
85
86
89
90
92
95
96
99
*/

/* numbers with odd 1s
1
2
4
7
8
11
13
14
16
19
21
22
25
26
28
31
32
35
37
38
41
42
44
47
49
50
52
55
56
59
61
62
64
67
69
70
73
74
76
79
81
82
84
87
88
91
93
94
97
98
*/
#include <stdio.h>
#include <assert.h>

int odd_ones(unsigned x);
int odd_ones_byte(unsigned char x);
int odd_ones_unoptimized(unsigned x);

int main(int argc, char const *argv[])
{
    for (unsigned counter = 0; counter < ~0; counter++) {
        assert(odd_ones(counter) == odd_ones_unoptimized(counter));
        // if (!!odd_ones_unoptimized(counter)) {
        //     printf("%d\n", counter);
        // }

    }
    
    return 0;
}

int odd_ones(unsigned x) {
    unsigned parity = x;
    parity = parity ^ (parity >> 16);
    parity = parity ^ (parity >> 8);
    parity = parity ^ (parity >> 4);
    parity = parity ^ (parity >> 2);
    parity = parity ^ (parity >> 1);
    parity = parity & 0x1u;
    return parity;
}

// int odd_ones(unsigned x) {
//     unsigned char b1 = x >> 24;
//     unsigned char b2 = x >> 16;
//     unsigned char b3 = x >> 8;
//     unsigned char b4 = x;
//     unsigned char xor = b1 ^ b2 ^ b3 ^ b4;
//     unsigned char parity = xor;
//     parity = parity ^ (xor << 1);
//     parity = parity ^ (xor << 2);
//     parity = parity ^ (xor << 3);
//     parity = parity ^ (xor << 4);
//     parity = parity ^ (xor << 5);
//     parity = parity ^ (xor << 6);
//     parity = parity ^ (xor << 7);
//     parity = parity ^ (xor << 8);
//     parity = parity & (char)0x80;
//     return !!parity;
// }

int odd_ones_unoptimized(unsigned x) {
    unsigned char b1 = x >> 24;
    unsigned char b2 = x >> 16;
    unsigned char b3 = x >> 8;
    unsigned char b4 = x;
    return !!((odd_ones_byte(b1) + odd_ones_byte(b2) + odd_ones_byte(b3) + odd_ones_byte(b4)) % 2);
}

int odd_ones_byte(unsigned char x) {
    int counter = 0;
    unsigned char current_bit;
    unsigned char bitmask;
    for (unsigned char i = 0; i < 8; i++) {
        bitmask = 1 << i;
        current_bit = x & bitmask;
        if (!!current_bit) {
            counter++;
        }
    }
    return !!(counter % 2);
}
