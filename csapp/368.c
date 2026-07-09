/*
In the following code, A and B are constants defined with #define:
*/
#define A 9
#define B 5

typedef struct {
    int x[A][B]; /* Unknown constants A and B */
    long y;
} str1;

typedef struct {
    char array[B];
    int t;
    short s[A];
    long u;
} str2;

void setVal(str1 *p, str2 *q) {
    long v1 = q->t;
    long v2 = q->u;
    p->y = v1+v2;
}

/*
Gcc generates the following code for setVal:

void setVal(str1 *p, str2 *q)
p in %rdi, q in %rsi

setVal:
    movslq 8(%rsi), %rax // move with sign-extension q->t into rax (must mean 5 <= B <= 8) (for alignment to make sense)
    addq 32(%rsi), %rax  // q->t += q->u  (8bytes)(4bytes int)(20 bytes)(8bytes long) (must mean 7 <= A <= 10) (for alignment to make sense)
    movq %rax, 184(%rdi) // (184 bytes)(8 bytes long) (must mean 177 <= 4(A*B) <= 184) (for alignment to make sense)
    ret

What are the values of A and B? (The solution is unique.)

// 5 <= B <= 8
// 7 <= A <= 10
// 177 <= 4(A*B) <= 184
// A = 9, B = 5
*/
