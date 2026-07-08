/*
For a function with prototype
long decode2(long x, long y, long z);
gcc generates the following assembly code:

decode2:
subq %rdx, %rsi // y -= z
imulq %rsi, %rdi // x *= y
movq %rsi, %rax // ret = y
salq $63, %rax // val <<= 63
sarq $63, %rax // val >>= 63
xorq %rdi, %rax // val ^= x
ret

Parameters x, y, and z are passed in registers %rdi, %rsi, and %rdx. The code
stores the return value in register %rax.
Write C code for decode2 that will have an effect equivalent to the assembly
code shown.
*/

long decode2(long x, long y, long z) {
    y -= z;
    x *= y;
    long val = y;
    val <<= 63;
    val >>= 63;
    val ^= x;
    return val;
}
