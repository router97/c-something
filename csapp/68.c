/*
The three functions in Figure 6.20 perform the same operation with varying degrees of spatial locality. 
Rank-order the functions with respect to the spatial locality enjoyed by each. 
Explain how you arrived at your ranking.
*/

/*
from best to worst:
1 - 2 - 3

1st references memory addresses sequentially
2nd is still pretty close together, but jumps back and forth more
3rd has huge jumps between memory locations
*/

/* (a) An array of structs */
#define N 1000

typedef struct {
    int vel[3];
    int acc[3];
} point;

point p[N];


/* (b) The clear1 function 
| Address      | 0           | 4           | 8           | 12          | 16          | 20          |
|--------------|-------------|-------------|-------------|-------------|-------------|-------------|
| Contents     | p[0].vel[0] | p[0].vel[1] | p[0].vel[2] | p[0].acc[0] | p[0].acc[1] | p[0].acc[2] |
| Access order | 1           | 2           | 3           | 4           | 5           | 6           |
*/
void clear1(point *p, int n)
{
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++)
            p[i].vel[j] = 0;
        for (j = 0; j < 3; j++)
            p[i].acc[j] = 0;
    }
}



/* (c) The clear2 function
| Address      | 0           | 4           | 8           | 12          | 16          | 20          |
|--------------|-------------|-------------|-------------|-------------|-------------|-------------|
| Contents     | p[0].vel[0] | p[0].vel[1] | p[0].vel[2] | p[0].acc[0] | p[0].acc[1] | p[0].acc[2] |
| Access order | 1           | 3           | 5           | 2           | 4           | 6           |
*/
void clear2(point *p, int n)
{
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            p[i].vel[j] = 0;
            p[i].acc[j] = 0;
        }
    }
}


/* (d) The clear3 function
| Address      | 0           | 12          | 24          | 36          | ... | 24n         | 24n+20      |
|--------------|-------------|-------------|-------------|-------------|-----|-------------|-------------|
| Contents     | p[0].vel[0] | p[0].acc[0] | p[1].vel[0] | p[1].acc[0] | ... | p[n].vel[2] | p[n].acc[2] |
| Access order | 1           | 1+n         | 2           | 2+n         | ... | k-n         | k           |
*/
void clear3(point *p, int n)
{
    int i, j;

    for (j = 0; j < 3; j++) {
        for (i = 0; i < n; i++)
            p[i].vel[j] = 0;
        for (i = 0; i < n; i++)
            p[i].acc[j] = 0;
    }
}
