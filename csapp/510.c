/*
As another example of code with potential load-store interactions, consider the
following function to copy the contents of one array to another:
*/

void copy_array(long *src, long *dest, long n)
{
    long i;
    for (i = 0; i < n; i++)
        dest[i] = src[i];
}

/*
Suppose a is an array of length 1,000 initialized so that each element a[i]
equals i.

A. What would be the effect of the call copy_array(a+1,a,999)?

array a = {1, 2, 3, 4, 5... 997, 998, 999, 999}

 a[0] a[1] a[2] a[3] a[4] a[5]          a[999]
┌────┬────┬────┬────┬────┬────┬         ┬────┐
│  0 │  1 │  2 │  3 │  4 │  5 │         │ 999│
└────┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴         ┴──┬─┘
  ┌────┬┴───┬┴───┬┴───┬┴────┘        ┌─────┘  
  ▼    ▼    ▼    ▼    ▼        ...   ▼        
┌────┬────┬────┬────┬────┬────┬    ┬────┬────┐
│ 0  │ 1  │ 2  │ 3  │ 4  │ 5  │    │998 │999 │
└────┴────┴────┴────┴────┴────┴    ┴────┴────┘
 a[0] a[1] a[2] a[3] a[4] a[5]     a[998]     


B. What would be the effect of the call copy_array(a,a+1,999)?

array a = {0, 0... 0, 0}

   ┌───┐┌───┐┌───┐┌───┐┌───┐┌──        ───┐   
   │   ▼│   ▼│   ▼│   ▼│   ▼│             ▼   
 a[0] a[1] a[2] a[3] a[4] a[5]          a[999]
┌────┬────┬────┬────┬────┬────┬         ┬────┐
│  0 │  1 │  2 │  3 │  4 │  5 │  ...    │ 999│
└────┴────┴────┴────┴────┴────┴         ┴────┘
   ┌───┐                                      
   │   ▼                                      
 a[0] a[1]    ───►   a[0] a[1]                
┌────┬────┬         ┌────┬────┬   ...         
│  0 │  1 │         │  0 │  0 │               
└────┴────┴         └────┴────┴               


C. Our performance measurements indicate that the call of part A has a CPE
of 1.2 (which drops to 1.0 when the loop is unrolled by a factor of 4), while
the call of part B has a CPE of 5.0. To what factor do you attribute this
performance difference?

Because in B, the memory address being read
has been written to in the previous iteration
so the read is dependent on the previous iteration's write


D. What performance would you expect for the call copy_array(a,a,999)?

same as A, there are no memory dependencies between iterations
an iteration's read doesn't depend on the previous iteration's write
*/
