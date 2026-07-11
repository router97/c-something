/*
Write a function in assembly code that matches the behavior of the function find_
range in Figure 3.51. Your code should contain only one floating-point comparison
instruction, and then it should use conditional moves to generate the correct result.
You might want to make use of the instruction cmovp (move if even parity). Test
your code on all 2^32 possible argument values. Web Aside asm:easm on page 214
describes how to incorporate functions written in assembly code into C programs.
*/

/*
typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x)
{
    int result;
    if (x < 0)
    result = NEG;
    else if (x == 0)
    result = ZERO;
    else if (x > 0)
    result = POS;
    else
    result = OTHER;
    return result;
}
*/

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x) {
    asm(
    "vxorps %xmm1, %xmm1, %xmm1 \n\t"
    "vucomiss %xmm1, %xmm0 \n\t"
    "movq $0, %r8 \n\t"
    "movq $1, %r9 \n\t"
    "movq $2, %r10 \n\t"
    "movq $3, %r11 \n\t"

    "cmovbq %r8, %rax \n\t"
    "cmoveq %r9, %rax \n\t"
    "cmovaq %r10, %rax \n\t"
    "cmovpq %r11, %rax \n\t"
    );
}
