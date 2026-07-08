/*
The code that follows shows an example of branching on an enumerated type
value in a switch statement. Recall that enumerated types in C are simply a way
to introduce a set of names having associated integer values. By default, the values
assigned to the names count from zero upward. In our code, the actions associated
with the different case labels have been omitted.
*/

/* Enumerated type creates set of constants numbered 0 and upward */
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1, long *p2, mode_t action)
{
    long result = 0;
    switch(action) {
    case MODE_A:
        result = *p2;
        *p2 = *p1;
        break;

    case MODE_B:
        result = *p1 + *p2;
        *p1 = result;
        break;

    case MODE_C:
        *p1 = 59;
        result = *p2;
        break;

    case MODE_D:
        *p1 = *p2;
        result = 27;
        break;

    case MODE_E:
        result = 27;
        break;

    default:
        result = 12;
        break;
    }
    return result;
}

/*
The part of the generated assembly code implementing the different actions is
shown in Figure 3.52. The annotations indicate the argument locations, the register
values, and the case labels for the different jump destinations.
Fill in the missing parts of the C code. It contained one case that fell through
to another—try to reconstruct this
*/

/*
p1 in %rdi, p2 in %rsi, action in %edx
.L8: // MODE_E
    movl $27, %eax // result = 27
    ret
.L3: // MODE_A
    movq (%rsi), %rax // result = *p2
    movq (%rdi), %rdx
    movq %rdx, (%rsi) // *p2 = *p1
    ret
.L5: // MODE_B
    movq (%rdi), %rax // result = *p1
    addq (%rsi), %rax // result += *p2
    movq %rax, (%rdi) // *p1 = result
    ret
.L6: // MODE_C
    movq $59, (%rdi) // *p1 = 59
    movq (%rsi), %rax // result = *p2
    ret
.L7: // MODE_D
    movq (%rsi), %rax // result = *p2
    movq %rax, (%rdi) // *p1 = result
    movl $27, %eax // result = 27
    ret
.L9: // default
    movl $12, %eax // result = 12
    ret
*/
