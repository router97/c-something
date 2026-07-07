/*
loop:
    movl %esi, %ecx // ecx = n (copied for shift)
    movl $1, %edx // mask = 1
    movl $0, %eax // result = 0
    jmp .L2
.L3:
    movq %rdi, %r8 // temp = x
    andq %rdx, %r8 // temp &= mask
    orq %r8, %rax // result |= temp
    salq %cl, %rdx // mask <<= n
.L2:
    testq %rdx, %rdx
    jne .L3 // if mask != 0
    rep; ret

A. Which registers hold program values x, n, result, and mask?
// result -> rax
// mask -> rdx
// x -> rdi
// n -> esi

B. What are the initial values of result and mask?
// result -> 0
// mask -> 1

C. What is the test condition for mask?
// mask != 0

D. How does mask get updated?
// left shift by low 8bits of n

E. How does result get updated?
// ORd with (x & mask)

F. Fill in all the missing parts of the C code.
*/
long loop(long x, long n)
{
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = mask << n) {
        result |= x & mask;
    }
    return result;
}
