#include <stdio.h>

int main(int argc, char const *argv[])
{
    char vchar = 0;
    short vshort = 0;
    int vint = 0;
    long unsigned vlongun = 0;
    long signed vlongs = 0;
    float vfloat = 0;
    double vdouble = 0;

    printf("%10s", "char : ");
    printf("%20llx : ", vchar);
    vchar -= 1;
    printf("%20llx\n", vchar);

    printf("%10s", "short : ");
    printf("%20llx : ", vshort);
    vshort -= 1;
    printf("%20llx\n", vshort);

    printf("%10s", "int : ");
    printf("%20llx : ", vint);
    vint -= 1;
    printf("%20llx\n", vint);

    printf("%10s", "long us : ");
    printf("%20llx : ", vlongun);
    vlongun -= 1;
    printf("%20llx\n", vlongun);

    printf("%10s", "long s : ");
    printf("%20llx : ", vlongs);
    vlongs -= 1;
    printf("%20llx\n", vlongs);

    printf("%10s", "float : ");
    printf("%20llx : ", vfloat);
    vfloat -= 1;
    printf("%20llx\n", vfloat);

    printf("%10s", "double : ");
    printf("%20llx : ", vdouble);
    vdouble -= 1;
    printf("%20llx\n", vdouble);

    return 0;
}
