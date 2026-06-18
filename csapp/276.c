#include <stdlib.h>
#include <string.h>

void *fake_calloc(size_t nmemb, size_t size);

int main(int argc, char const *argv[])
{
    return 0;
}

void *fake_calloc(size_t nmemb, size_t size) {
    if ((nmemb == 0) || (size == 0)) {
        return NULL;
    }
    
    size_t prod = nmemb * size;
    if ((prod / nmemb) != size) {
        return NULL;
    }

    void *ptr = malloc(prod);
    if (ptr == NULL) {
        return NULL;
    }
    memset(ptr, 0, prod);
    return ptr;
}
