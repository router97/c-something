/*
Suppose we wish to write a procedure that computes the inner product of two
vectors u and v. An abstract version of the function has a CPE of 14-18 with x86-
64 for different types of integer and floating-point data. By doing the same sort
of transformations we did to transform the abstract program combine1 into the
more efficient combine4, we get the following code:
*/

/* Inner product. Accumulate in temporary */
void inner4(vec_ptr u, vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;

    for (i = 0; i < length; i++) {
        sum = sum + udata[i] * vdata[i];
    }
    *dest = sum;
}

/*
Our measurements show that this function has CPEs of 1.50 for integer data
and 3.00 for floating-point data. For data type double, the x86-64 assembly code
for the inner loop is as follows:

Inner loop of inner4. data_t = double, OP = *
udata in %rbp, vdata in %rax, sum in %xmm0
i in %rcx, limit in %rbx
.L15:                               loop:
vmovsd 0(%rbp,%rcx,8), %xmm1            Get udata[i]
vmulsd (%rax,%rcx,8), %xmm1, %xmm1      Multiply by vdata[i]
vaddsd %xmm1, %xmm0, %xmm0              Add to sum
addq $1, %rcx                           Increment i
cmpq %rbx, %rcx                         Compare i:limit
jne .L15                                If !=, goto loop

Assume that the functional units have the characteristics listed in Figure 5.12.

A. Diagram how this instruction sequence would be decoded into operations
and show how the data dependencies between them would create a critical
path of operations, in the style of Figures 5.13 and 5.14.

                                   ┌──────┐ 
                                   │ xmm0 │ 
                                   └┬─────┘ 
────────────────────────────────────┼───────
         ┌──────┐  ┌──────┐         │       
 udata[i]│ load │  │ load │vdata[i] │       
         └─────┬┘  └┬─────┘         │       
               │    │               │       
              ┌▼────▼┐              │       
              │ fmul │              │       
              └─────┬┘              │       
                    │          ┌────▼─┐     
                    └─────────►│ fadd │     
                               └────┬─┘     
────────────────────────────────────┼───────
                                   ┌▼─────┐ 
                                   │ xmm0 │ 
                                   └──────┘ 


B. For data type double, what lower bound on the CPE is determined by the
critical path?

floating-point addition's latency is 3 cycles, so 3


C. Assuming similar instruction sequences for the integer code as well, what
lower bound on the CPE is determined by the critical path for integer data?

integer addition's latency is 1, so 1


D. Explain how the floating-point versions can have CPEs of 3.00, even though
the multiplication operation requires 5 clock cycles.

the multiplication can be pipelined, as it only depends on the load output. The issue time is 1.
*/
