/*
The following problem illustrates the way memory aliasing can cause unexpected
program behavior. Consider the following procedure to swap two values:
*/

/* Swap value x at xp with value y at yp */
void swap(long *xp, long *yp)
{
    *xp = *xp + *yp; /* x+y       */
    *yp = *xp - *yp; /* x+y-y = x */
    *xp = *xp - *yp; /* x+y-x = y */
}

/*
If this procedure is called with xp equal to yp, what effect will it have?

*xp = *xp + *yp
*xp = 2x

*yp = 2x - 2x
*yp = 0

*xp = 0 - 0
*/
