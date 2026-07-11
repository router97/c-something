/*
Write a function in assembly code that matches the behavior of the function find_
range in Figure 3.51. Your code should contain only one floating-point comparison
instruction, and then it should use conditional branches to generate the correct
result. Test your code on all 2^32 possible argument values. Web Aside asm:easm
on page 214 describes how to incorporate functions written in assembly code into
C programs.
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
    "jp .other \n\t"
    "jb .neg \n\t"
    "je .zero \n\t"
    "ja .pos \n\t"
    
    ".other: \n\t"
    "movl $3, %eax \n\t"
    "jmp .end \n\t"

    ".neg: \n\t"
    "movl $0, %eax \n\t"
    "jmp .end \n\t"

    ".zero: \n\t"
    "movl $1, %eax \n\t"
    "jmp .end \n\t"

    ".pos: \n\t"
    "movl $2, %eax \n\t"
    "jmp .end \n\t"

    ".end:"
    );
}
