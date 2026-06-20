int float_le(float x, float y);

int main(int argc, char const *argv[])
{
    return 0;
}

int float_le(float x, float y) {
    unsigned ux = *(unsigned*)&x;
    unsigned uy = *(unsigned*)&y;

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;
    
    return ((ux & 0x7FFFFFFF) == 0) && ((uy & 0x7FFFFFFF) == 0) ? 1 : (
        sx > sy ? 1 : 
        (sy > sx ? 0 : 
            sx == 1 ?
                ((ux & 0x7FFFFFFF) >= (uy & 0x7FFFFFFF) ? 1 : 
                    0
                )
                :
                ((ux & 0x7FFFFFFF) <= (uy & 0x7FFFFFFF) ? 1 : 
                0
                )
        ));
}
