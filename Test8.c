#include "mymalloc.h"
#include <stdio.h>

void main()
{
    void* p = malloc(2);
    free(p);
    printf("p has been freed\n");
    free(p + 1);
}