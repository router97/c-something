/*
You are charged with maintaining a large C program, and you come across the
following code:
*/

#define CNT 7

typedef struct {
    long idx;
    long x[4];
} a_struct;

typedef struct {
    int first;
    a_struct a[CNT];
    int last;
} b_struct;

void test(long i, b_struct *bp)
{
    int n = bp->first + bp->last;
    a_struct *ap = &bp->a[i];
    ap->x[ap->idx] = n;
}

/*
The declarations of the compile-time constant CNT and the structure a_struct
are in a file for which you do not have the necessary access privilege. Fortunately,
you have a copy of the .o version of code, which you are able to disassemble with
the objdump program, yielding the following disassembly:

void test(long i, b_struct *bp)
i in %rdi, bp in %rsi

0000000000000000 <test>:
0:  8b 8e 20 01 00 00   mov     0x120(%rsi),%ecx        // n = bp->last
6:  03 0e               add     (%rsi),%ecx             // n += bp->first
8:  48 8d 04 bf         lea     (%rdi,%rdi,4),%rax      // rax = i + i*4 = 5i
c:  48 8d 04 c6         lea     (%rsi,%rax,8),%rax      // rax = bp + 40i
10: 48 8b 50 08         mov     0x8(%rax),%rdx          // rdx = (bp + 40i + 8) (rdx = ap->idx)
14: 48 63 c9            movslq  %ecx,%rcx               // sign-extend int n into long rcx
17: 48 89 4c d0 10      mov     %rcx,0x10(%rax,%rdx,8)  // a-offset + 8  + idx*8 + 8 = n
1c: c3                  retq

Using your reverse engineering skills, deduce the following:

A. The value of CNT.
CNT = 7

B. A complete declaration of structure a_struct. Assume that the only fields
in this structure are idx and x, and that both of these contain signed values.

sizeof(b_struct) = 292 bytes

0   : first (4 bytes)
4   : ALIGN (4 bytes)
8   : a[0]  (40 bytes)
48  : a[1]  (40 bytes)
88  : a[2]  (40 bytes)
128 : a[3]  (40 bytes)
168 : a[4]  (40 bytes)
208 : a[5]  (40 bytes)
248 : a[6]  (40 bytes)
288 : last  (4 bytes)


sizeof(a_struct) = 40 bytes

0   : idx   (8 bytes)
8   : x[0]  (8 bytes)
16  : x[1]  (8 bytes)
24  : x[2]  (8 bytes)
32  : x[3]  (8 bytes)
*/
