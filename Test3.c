#include "mymalloc.h"
#include <stdio.h>

void main()
{
    int i;
    for(i = 0; i < 5; i++){
        int* p = mymalloc(sizeof(int), __FILE__, __LINE__);
        *p = i;
        printf("address: %p, value: %d\n",p, *p);
    }
}