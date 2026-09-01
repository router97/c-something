/*
The heart of the recent hit game SimAquarium is a tight loop that calculates the
average position of 512 algae. You are evaluating its cache performance on a
machine with a 2,048-byte direct-mapped data cache with 32-byte blocks (B = 32).
You are given the following definitions:
*/

struct algae_position {
    int x;
    int y;
};

struct algae_position grid[32][32];
int total_x = 0, total_y = 0;
int i, j;

/*
You should also assume the following:

. sizeof(int) = 4.

. grid begins at memory address 0.

. The cache is initially empty.

. The only memory accesses are to the entries of the array grid. Variables i, j,
total_x, and total_y are stored in registers.

Determine the cache performance for the following code:
*/

for (i = 31; i >= 0; i--) {
    for (j = 31; j >= 0; j--) {
        total_x += grid[i][j].x;
    }
}

for (i = 31; i >= 0; i--) {
    for (j = 31; j >= 0; j--) {
        total_y += grid[i][j].y;
    }
}

/*
A. What is the total number of reads?
32 * 32 = 1024 elements in grid
each element in a grid is accessed twice
1024 * 2 = 2048 reads
*/

/*
B. What is the total number of reads that miss in the cache?
each grid is 1024 * 8 / 32 = 256 memory blocks

there are 2048 / 32 = 64 cache lines

a memory block contains 4 elements
1 out of 4 reads will be a miss

at the beginning of the second loop, the previously cached lines wont be used
because they are at the beginning of the array, and it will access the end

1024 / 4 = 256 misses per grid
512 misses overall
*/

/*
C. What is the miss rate?
512 / 2048 * 100 = 25%
*/
