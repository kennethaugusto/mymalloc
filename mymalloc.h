#ifndef MYMALLOC_H
#define MYMALLOC_H

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

// Macros for error reporting
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

#endif /* MYMALLOC_H */
