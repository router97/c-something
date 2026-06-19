int threefourths(int x);

int main(int argc, char const *argv[])
{
    return 0;
}

int threefourths(int x) {
    int xs = x >> 31;

    int remainder = x & 0x00000003;
    remainder = remainder | (xs & 0xFFFFFFFC);

    int bias = 3 & xs;
    int quot = (x + bias) >> 2;

    int prod = (quot << 1) + quot;

    int remainderprod = (remainder << 1) + remainder;
    int remainderquot = (remainderprod + bias) >> 2;
    return prod + remainderquot;
}
