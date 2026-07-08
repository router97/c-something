/*
Consider the following source code, where R, S, and T are constants declared with
#define:
*/

long A[R][S][T];

long store_ele(long i, long j, long k, long *dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
}

/*
In compiling this program, gcc generates the following assembly code:

long store_ele(long i, long j, long k, long *dest)
i in %rdi, j in %rsi, k in %rdx, dest in %rcx

store_ele:
    leaq (%rsi,%rsi,2), %rax
    leaq (%rsi,%rax,4), %rax
    movq %rdi, %rsi
    salq $6, %rsi
    addq %rsi, %rdi
    addq %rax, %rdi
    addq %rdi, %rdx          // index = 65i + 13j + k = 13*5i + 13j + k
    movq A(,%rdx,8), %rax
    movq %rax, (%rcx)        // *dest = A[index]
    movl $3640, %eax
    ret

A. Extend Equation 3.1 from two dimensions to three to provide a formula for
the location of array element A[i][j][k].

// D[R][C];
// &D[i][j] = xD + L(C * i + j)

// A[R][S][T];
// &A[i][j][k] = xD + L(i*ST + j*T + k)

B. Use your reverse engineering skills to determine the values of R, S, and T
based on the assembly code.

// R -> 3640 / (13*5*8) = 7
// S -> 5
// T -> 13
*/
