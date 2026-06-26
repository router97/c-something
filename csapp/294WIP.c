typedef unsigned float_bits;

float_bits float_twice(float_bits f);

int main(int argc, char const *argv[])
{
    return 0;
}

float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF) {
        return f;
    }

    if (exp > 0) {
        exp += 1;
    } else {
        frac <<= 1;

        if (frac & 0x800000) {
            frac &= 0x7FFFFF;
            exp = 1;
        }
    }

    return (sign << 31) | (exp << 23) | frac;
}
