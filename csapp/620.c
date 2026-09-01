/*
Given the assumptions of Practice Problem 6.18, determine the cache performance of the following code:
*/

for (i = 31; i >= 0; i--){
    for (j = 31; j >= 0; j--) {
        total_x += grid[i][j].x;
        total_y += grid[i][j].y;
    }
}

with a 2,048-byte direct-mapped data cache with 32-byte blocks (B = 32).
2048 / 32 = 64 lines

Elem            Line        Elem            Line
grid[0][0-3]    0           grid[1][0-3]    8
grid[0][4-7]    1           grid[1][4-7]    9
grid[0][8-11]   2           grid[1][8-11]   10
grid[0][12-15]  3           grid[1][12-15]  11
grid[0][16-19]  4           grid[1][16-19]  12
grid[0][20-23]  5           grid[1][20-23]  13
grid[0][24-27]  6           grid[1][24-27]  14
grid[0][28-31]  7           grid[1][28-31]  15
...
grid[30][0-3]   48          grid[31][0-3]   56
grid[30][4-7]   49          grid[31][4-7]   57
grid[30][8-11]  50          grid[31][8-11]  58
grid[30][12-15] 51          grid[31][12-15] 59
grid[30][16-19] 52          grid[31][16-19] 60
grid[30][20-23] 53          grid[31][20-23] 61
grid[30][24-27] 54          grid[31][24-27] 62
grid[30][28-31] 55          grid[31][28-31] 63


A. What is the total number of reads?
2048 reads

B. What is the total number of reads that hit in the cache?
2048 * 3/4 = 1536

ITER 0:
OP          Elem            Status
load        grid[31][31]     MISS :: load grid[31][28-31] into line 63
load        grid[31][30]     HIT
load        grid[31][29]     HIT
load        grid[31][28]     HIT
load        grid[31][27]     MISS :: load grid[31][24-27] into line 62
load        grid[31][26]     HIT
load        grid[31][25]     HIT
load        grid[31][24]     HIT
...


C. What is the hit rate?
1536 / 2048 * 100 = 75%

D. What would the hit rate be if the cache were twice as big?
if the block size doesnt change, the same
