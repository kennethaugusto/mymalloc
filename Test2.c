#include "mymalloc.h"
#include <stdio.h>

void main()
{
    double* p = mymalloc(sizeof(double), __FILE__, __LINE__);
    *p = 5;
    printf("address: %p, value: %f\n",p, *p);
    free(p);
}