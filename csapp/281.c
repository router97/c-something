unsigned a(unsigned k);
unsigned b(unsigned j, unsigned k);

int main(int argc, char const *argv[])
{
    return 0;
}

unsigned a(unsigned k) {
    return (~0) << k;
}

unsigned b(unsigned j, unsigned k) {
    return (~((~0) << k)) << j;
}
