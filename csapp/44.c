/*
Write Y86-64 code to implement a recursive product function rproduct, based
on the following C code:
*/

long rproduct(long *start, long count)
{
    if (count <= 1)
        return 1;
    return *start * rproduct(start+1, count-1);
}

/*
start in %rdi, count in %rsi

rproduct:
    iaddq $-1, %rsi
    jle .early

    pushq %r12

    mrmovq (%rdi), %r12
    iaddq $8, %rdi
    call rproduct
    imulq %r12, %rax

    popq %r12
    ret

.early:
    irmovq $1, %rax
    ret
*/

/*
Use the same argument passing and register saving conventions as x86-64 code
does. You might find it helpful to compile the C code on an x86-64 machine and
then translate the instructions to Y86-64.
*/
