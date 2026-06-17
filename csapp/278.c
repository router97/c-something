int divide_power2(int x, int k);

int main(int argc, char const *argv[])
{
    return 0;
}

int divide_power2(int x, int k) {
    int xs = x >> 31;
    int bias = ((1<<k)-1) & (xs);
    return (x + bias) >> k;
}
