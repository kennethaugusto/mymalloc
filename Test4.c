#include "mymalloc.h"
#include <stdio.h>

void main()
{
    int i;
    int* p = mymalloc(5 * sizeof(int), __FILE__, __LINE__);
    for(i = 0; i < 5; i++){
        p[i] = i;
    }
    for (i = 0; i < 5; i++){
        printf("address: %p, value: %d\n", p + i, p[i]);
     }
    myfree(p, __FILE__, __LINE__);
}