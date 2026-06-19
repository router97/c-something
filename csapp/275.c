unsigned unsigned_high_prod(unsigned x, unsigned y);
int signed_high_prod(int x, int y);

int main(int argc, char const *argv[])
{
    return 0;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int shp = signed_high_prod(x, y);
    unsigned sx = x >> 31;
    unsigned sy = y >> 31;
    unsigned uhp = shp + (x * sy) + (y * sx);
    return uhp;
}

int signed_high_prod(int x, int y) {
    int64_t lx = x;
    int64_t ly = y;
    int64_t lprod = lx * ly;
    int high_prod = lprod >> 32;
    return high_prod;
}
