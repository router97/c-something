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
            exp == 0;
            frac |= 0x800000;
        }

        unsigned discarded = frac & 0x00000001;
        frac >>= 1;

        if (discarded) {
            if (frac & 0x00000001) {
                frac++;
            }
        }
    }
    
    return (sign << 31) | (exp << 23) | frac;
}
