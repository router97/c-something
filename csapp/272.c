#include <string.h>

void copy_int(int val, void *buf, int maxbytes);

int main(int argc, char const *argv[])
{
    return 0;
}

void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes >= (int)sizeof(val))
    memcpy(buf, (void *) &val, sizeof(val));
}
