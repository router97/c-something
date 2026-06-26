typedef unsigned float_bits;

float_bits float_half(float_bits f);

int main(int argc, char const *argv[])
{
    return 0;
}

float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    
    if (exp == 0xFF) { 
        return f;
    }

    if (exp > 1) {
        exp -= 1;
    } else {
        if (exp == 1) {
            exp = 0;
            frac |= 0x800000;
        }

        if ((frac & 0x1) && (frac & 0x2)) {
            frac += 2;
        }
        frac >>= 1;
    }
    
    return (sign << 31) | (exp << 23) | frac;
}
