int k17(int x);
int km7(int x);
int k60(int x);
int km112(int x);

int main(int argc, char const *argv[])
{
    return 0;
}

int k17(int x) {
    return (x << 4) + x;
}

int km7(int x) {
    return -((x << 3) - x);
}

int k60(int x) {
    return (x << 6) - (x << 2);
}

int km112(int x) {
    return -((x << 7) - (x << 4));
}
