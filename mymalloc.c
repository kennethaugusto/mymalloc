#include <stdio.h>
#include <strings.h>

#include "mymalloc.h"

#define MEMSIZE 4096

struct metadata
{
	struct metadata *prev, *next;
	int isFree;
	int size;
};

static char memblock[MEMSIZE];
static const int entriesSize = MEMSIZE/sizeof(struct metadata)+1;
static void *memEntries[MEMSIZE/sizeof(struct metadata)+1] = {0};

static int getFreeIndex() {
	int i;
	for (i = 0; i < entriesSize; i++)
		if (memEntries[i] == 0) 
			return i;
	return 1;
}

void *mymalloc(size_t size, char *file, int line)
{
	static int initialized = 0;
	struct metadata *p;
	struct metadata *next;
	static struct metadata *root;
	
	if (size <= 0) {
        fprintf(stderr, "%s:%d:malloc: Size is 0 or smaller than 0\n", file, line);
        return NULL;
    }

    if (size > MEMSIZE) {
        fprintf(stderr, "%s:%d:malloc: Not enough memory for request\n", file, line);
        return NULL;
    }

	if (!initialized)
	{
		root = (struct metadata*) memblock;
		root->prev = 0;
		root->next = 0;
		root->size = MEMSIZE - sizeof(struct metadata);
		root->isFree = 1;
		initialized = 1;
		memEntries[getFreeIndex()] = memblock;
	}
	p = root;
	while (p != 0) {
		if (p->size < size || !p->isFree) {
			p = p->next;
		}
		else if (p->size < (size + sizeof(struct metadata))) {
			p->isFree = 0;
			return (char*)p + sizeof(struct metadata);
		}
		else {
			next = (struct metadata*)((char*)p + sizeof(struct metadata) + size);
			next->prev = p;
			next->next = p->next;
			next->size = p->size - sizeof(struct metadata) - size;
			next->isFree = 1;
			memEntries[getFreeIndex()] = next;
			p->size = size;
			p->isFree = 0;
			p->next = next;
			return (char*)p + sizeof(struct metadata);
		}
	}
	fprintf(stderr, "Insufficient memory space requested (%ld bytes) in FILE: '%s' on LINE: '%d'\n", size, file, line);
	return 0;
}

void myfree(void *p, char *file, int line)
{
	struct metadata *ptr;
	struct metadata *prev;
	struct metadata *next;

	if (p == NULL) {
		fprintf(stderr, "Pointer is NULL in file, free failed in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}

	ptr = (struct metadata*)((char*)p - sizeof(struct metadata));
	
	int i;
	int valid = 0;
	for (i = 0; i < entriesSize; i++) {
		if (ptr == memEntries[i] && !ptr->isFree) {
			valid = 1;
			break;
		}
	}
	if (!valid) {
		fprintf(stderr, "Attempting to free memory that was not malloced in FILE: '%s' on LINE: '%d'\n", file, line);
		return;
	}

	if ((prev = ptr->prev) != 0 && prev->isFree) {
		prev->size += sizeof(struct metadata) + ptr->size;
		memEntries[i] = 0;
	} else {
		ptr->isFree = 1;
		prev = ptr;
	}
	if ((next = ptr->next) != 0 && next->isFree) {
		prev->size += sizeof(struct metadata) + next->size;
		prev->next = next->next;
		for (i = 0; i < entriesSize; i++) {
			if (next == memEntries[i]) {
				memEntries[i] = 0;
				break;
			}
		}
	}
}