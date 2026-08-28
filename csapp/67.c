Permute the loops in the following function so that it scans the three-dimensional
array a with a stride-1 reference pattern.

int productarray3d(int a[N][N][N])
{
    int i, j, k, product = 1;

    for (i = N-1; i >= 0; i--) {
        for (j = N-1; j >= 0; j--) {
            for (k = N-1; k >= 0; k--) {
                product *= a[j][k][i];
            }
        }
    }
    return product;
}

int productarray3d2(int a[N][N][N])
{
    int i, j, k, product = 1;

    for (j = N-1; j >= 0; j--) {
        for (k = N-1; k >= 0; k--) {
            for (i = N-1; i >= 0; i--) {
                product *= a[j][k][i];
            }
        }
    }
    return product;
}
