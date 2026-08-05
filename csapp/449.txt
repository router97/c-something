/*
Modify the code you wrote for Problem 4.47 to implement the test and swap in the
bubblesort function (lines 6–11) using no jumps and just one conditional move.
*/

*i in %rdx

// load old values
mrmovq 8(%rdx), %r9 // r9 = *(i+1)
mrmovq (%rdx), %r8  // r8 = *i

xorq %r13, %r13     // r13 = 000..

rrmovq %r9, %r12
subq %r8, %r12      // set cc

irmovq $-1, %r12
cmovl %r12, %r13    // r13 = 111.. if swap      000.. if not

rrmovq %r8, %r11    // r11 = *i
rrmovq %r9, %r12    // r12 = *(i+1)

subq %r9, %r11      // r11 = *i - *(i+1)
subq %r8, %r12      // r12 = *(i+1) - *i

andq %r13, %r11     // *i - *(i+1) if swap      000.. if not
andq %r13, %r12     // *(i+1) - *i if swap      000.. if not

addq %r9, %r11      // r11 = *i if swap         *(i+1) if not swap
addq %r8, %r12      // r12 = *(i+1) if swap     *i if not swap

rmmovq %r11, 8(%rdx)
rmmovq %r12, (%rdx)
