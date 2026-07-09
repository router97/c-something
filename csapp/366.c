/*
Consider the following source code, where NR and NC are macro expressions declared with #define 
that compute the dimensions of array A in terms of parameter n. 
This code computes the sum of the elements of column j of the array.
*/

#define NR(n) (3*n)
#define NC(n) (1 + 4*n)

long sum_col(long n, long A[NR(n)][NC(n)], long j) {
    long i;
    long result = 0;
    for (i = 0; i < NR(n); i++)
        result += A[i][j];
    return result;
}

/*
In compiling this program, gcc generates the following assembly code:

long sum_col(long n, long A[NR(n)][NC(n)], long j)
n in %rdi, A in %rsi, j in %rdx

sum_col:
    leaq 1(,%rdi,4), %r8        // t1 = 1 + 4*n
    leaq (%rdi,%rdi,2), %rax
    movq %rax, %rdi             // n = 3*n (n = NR(n))
    testq %rax, %rax
    jle .L4                     // if NR(n) < 0 : return 0
    salq $3, %r8                // t1 <<= 3 (t1 = 8 + 32*n)
    leaq (%rsi,%rdx,8), %rcx    // t2 = A[0][j]
    movl $0, %eax               // result = 0
    movl $0, %edx               // set edx to 0 and it is now i
.L3:
    addq (%rcx), %rax           // result += A[i][j]
    addq $1, %rdx               // i += 1
    addq %r8, %rcx              // t2 += t1 (switch to next row, same column)
    cmpq %rdi, %rdx             
    jne .L3                     // i != NR(n) : goto loop
    rep; ret
.L4:
    movl $0, %eax               // result = 0
    ret

Use your reverse engineering skills to determine the definitions of NR and NC
*/
