/*
In Section 3.6.8, we saw that a common way to implement switch statements is to
create a set of code blocks and then index those blocks using a jump table. Consider
the C code shown in Figure 4.69 for a function switchv, along with associated
test code.

Implement switchv in Y86-64 using a jump table. Although the Y86-64 instruction set 
does not include an indirect jump instruction, you can get the same
effect by pushing a computed address onto the stack and then executing the ret
instruction. Implement test code similar to what is shown in C to demonstrate that
your implementation of switchv will handle both the cases handled explicitly as
well as those that trigger the default case.
*/


#include <stdio.h>
/* Example use of switch statement */

long switchv(long idx) {
    long result = 0;
    switch(idx) {
    case 0:
        result = 0xaaa;
        break;
    case 2:
    case 5:
        result = 0xbbb;
        break;
    case 3:
        result = 0xccc;
        break;
    default:
        result = 0xddd;
    }
    return result;
}

/* Testing Code */
#define CNT 8
#define MINVAL -1

int main() {
    long vals[CNT];
    long i;
    for (i = 0; i < CNT; i++) {
        vals[i] = switchv(i + MINVAL);
        printf("idx = %ld, val = 0x%lx\n", i + MINVAL, vals[i]);
    }
    return 0;
}

/*
.pos 0
irmovq stack, %rsp
call main
halt

.align 8
table:
    .quad L0 # 0
    .quad L4 # 1
    .quad L1 # 2
    .quad L3 # 3
    .quad L4 # 4
    .quad L2 # 5

main:
    pushq %r10
    irmovq $64, %rdi
    subq %rdi, %rsp # allocate space for long vals[CNT]
    xorq %r10, %r10
    # vals in %rsp
    # i in %r10
    
.for_start:
    rrmovq %r10, %r8
    isubq $8, %r8
    jge .for_end
    
    rrmovq %r10, %rdi
    iaddq $-1, %rdi
    call switchv
    
    xorq %r8, %r8
    addq %r10, %r8
    addq %r10, %r8
    addq %r10, %r8
    addq %r10, %r8
    addq %r10, %r8
    addq %r10, %r8
    addq %r10, %r8
    addq %r10, %r8
    addq %rsp, %r8
    rmmovq %rax, (%r8)
    
    iaddq $1, %r10
    jmp .for_start
.for_end:
    iaddq $64, %rsp
    popq %r10
    xorq %rax, %rax
    ret
    
switchv:
    xorq %rax, %rax
    rrmovq %rdi, %r8
    isubq $0, %r8
    jl L4
    
    rrmovq %rdi, %r8
    isubq $5, %r8
    jg L4
    
    xorq %r8, %r8
    addq %rdi, %r8
    addq %rdi, %r8
    addq %rdi, %r8
    addq %rdi, %r8
    addq %rdi, %r8
    addq %rdi, %r8
    addq %rdi, %r8
    addq %rdi, %r8
    iaddq table, %r8
    
    mrmovq (%r8), %rdi
    pushq %rdi
    ret
    
L0:
    irmovq $0xAAA, %rax
    jmp .switch_end
L1:
L2:
    irmovq $0xBBB, %rax
    jmp .switch_end
L3:
    irmovq $0xCCC, %rax
    jmp .switch_end
L4:
    irmovq $0xDDD, %rax
.switch_end:
    ret

.pos 0x400
stack:
*/
