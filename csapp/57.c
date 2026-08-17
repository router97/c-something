Modify the code for combine5 to unroll the loop by a factor k = 5

/* 2 x 1 loop unrolling */
void combine5(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
        acc = (acc OP data[i]) OP data[i+1];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}

/* 5 x 1 loop unrolling */
void combine5(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length-4;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 5 elements at a time */
    for (i = 0; i < limit; i+=5) {
        acc = (((((acc OP data[i]) OP data[i+1]) OP data[i+2]) OP data[i+3]) OP data[i+4]);
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}
