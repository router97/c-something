/*
Consider the following function for computing the product of an array of n
doubleprecision numbers. We have unrolled the loop by a factor of 3.
*/

double aprod(double a[], long n)
{
    long i;
    double x, y, z;
    double r = 1;
    for (i = 0; i < n-2; i+= 3) {
        x = a[i]; y = a[i+1]; z = a[i+2];
        r = r * x * y * z; /* Product computation */
    }
    for (; i < n; i++)
        r *= a[i];
    return r;
}

/*
For the line labeled “Product computation,” we can use parentheses to create 
five different associations of the computation, as follows:
*/

r = ((r * x) * y) * z;
/* A1 // CRITICAL PATH : 3mul
┌───┐ ┌───┐ ┌───┐ ┌───┐
│ r │ │ x │ │ y │ │ z │
└─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
  │     │     │     │  
  └┬───┬┘     │     │  
   │mul│      │     │  
   └─┬─┘      │     │  
     │        │     │  
     └───┬───┬┘     │  
         │mul│      │  
         └─┬─┘      │  
           │        │  
           └───┬───┬┘  
               │mul│   
               └─┬─┘   
                 ▼     
                 r     
*/

r = (r * (x * y)) * z;
/* A2 // CRITICAL PATH : 3mul
┌───┐ ┌───┐ ┌───┐ ┌───┐
│ r │ │ x │ │ y │ │ z │
└─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
  │     │     │     │  
  │     └┬───┬┘     │  
  │      │mul│      │  
  │      └─┬─┘      │  
  │        │        │  
  └┬───┬───┘        │  
   │mul│            │  
   └─┬─┘            │  
     │              │  
     └─────────┬───┬┘  
               │mul│   
               └─┬─┘   
                 ▼     
                 r     
*/
r = r * ((x * y) * z); /* A3 */
/* A3 // CRITICAL PATH: 3mul
┌───┐ ┌───┐ ┌───┐ ┌───┐
│ r │ │ x │ │ y │ │ z │
└─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
  │     │     │     │  
  │     └┬───┬┘     │  
  │      │mul│      │  
  │      └─┬─┘      │  
  │        │        │  
  │        └───┬───┬┘  
  │            │mul│   
  │            └─┬─┘   
  │              │     
  └┬───┬─────────┘     
   │mul│               
   └─┬─┘               
     ▼                 
     r                 
*/
r = r * (x * (y * z));
/* A4 // CRITICAL PATH: 3mul
┌───┐ ┌───┐ ┌───┐ ┌───┐
│ r │ │ x │ │ y │ │ z │
└─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
  │     │     │     │  
  │     │     └┬───┬┘  
  │     │      │mul│   
  │     │      └─┬─┘   
  │     │        │     
  │     └┬───┬───┘     
  │      │mul│         
  │      └─┬─┘         
  │        │           
  └┬───┬───┘           
   │mul│               
   └─┬─┘               
     ▼                 
     r                 
*/
r = (r * x) * (y * z); 
/* A5 // CRITICAL PATH: 2mul
┌───┐ ┌───┐ ┌───┐ ┌───┐
│ r │ │ x │ │ y │ │ z │
└─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
  │     │     │     │  
  └┬───┬┘     └┬───┬┘  
   │mul│       │mul│   
   └─┬─┘       └─┬─┘   
     │           │     
     └───┬───┬───┘     
         │mul│         
         └─┬─┘         
           ▼           
           r           
*/

/*
Assume we run these functions on a machine where floating-point multiplication
has a latency of 5 clock cycles. Determine the lower bound on the CPE set by
the data dependencies of the multiplication. (Hint: It helps to draw a data-flow
representation of how r is computed on every iteration.)
*/

/*
lowest amount of cycles per iteration is 10
due to unrolling by 3, CPE = 10/3 = 3.3
*/
