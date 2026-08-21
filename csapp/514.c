/*
Write a version of the inner product procedure described in Problem 5.13 that
uses 6 x 1 loop unrolling. For x86-64, our measurements of the unrolled version
give a CPE of 1.07 for integer data but still 3.01 for both floating-point data.
*/

void inner4(vec_ptr u, vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(u);
    long limit = length-5;
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;

    for (i = 0; i < limit; i+=6) {
        sum = sum + (
            (udata[i] * vdata[i]) + 
            (udata[i+1] * vdata[i+1]) + 
            (udata[i+2] * vdata[i+2]) + 
            (udata[i+3] * vdata[i+3]) +
            (udata[i+4] * vdata[i+4]) + 
            (udata[i+5] * vdata[i+5])
        );
    }

    for (; i < length; i++) {
        sum = sum + (udata[i] * vdata[i]);
    }
    *dest = sum;
}

/*
┌──────┐                                     
│ load ├──►──────┐                           
├──────┤  │ imul │                           
│ load ├──►─────┬┘                           
└──────┘        └────►──────┐                
                     │ iadd │                
┌──────┐        ┌────►───┬──┘                
│ load ├──►─────┼┐       │                   
├──────┤  │ imul │       │                   
│ load ├──►──────┘       │                   
└──────┘                 │                   
                         │                   
┌──────┐                 │                   
│ load ├──►──────┐   ┌───▼──┐                
├──────┤  │ imul ├───► iadd │                
│ load ├──►──────┘   └───┬──┘                
└──────┘                 │                   
                         │                   
┌──────┐                 │                   
│ load ├──►──────┐   ┌───▼──┐        ┌──────┐
├──────┤  │ imul ├───► iadd │        │ sum  │
│ load ├──►──────┘   └───┬──┘        └───┬──┘
└──────┘                 │               │   
                         │               │   
┌──────┐                 │               │   
│ load ├──►──────┐   ┌───▼──┐            │   
├──────┤  │ imul ├───► iadd │            │   
│ load ├──►──────┘   └───┬──┘            │   
└──────┘                 │               │   
                         │               │   
┌──────┐                 │               │   
│ load ├──►──────┐   ┌───▼──┐        ┌───▼──┐
├──────┤  │ imul ├───► iadd ├────────► iadd │
│ load ├──►──────┘   └──────┘        └───┬──┘
└──────┘                                 │   
                                     ┌───▼──┐
                                     │ sum  │
                                     └──────┘

A. Explain why any (scalar) version of an inner product procedure running on
an Intel Core i7 Haswell processor cannot achieve a CPE less than 1.00.

for integers, multiplication throughput limits CPE to 1
for floating-point, addition throughput limits CPE to 1


B. Explain why the performance for floating-point data did not improve with
loop unrolling.

without adding additional accumulators, can't go past the latency bound
*/
