#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * struct block_head - stores metadata for each block
 * @total_bytes: total number of bytes occupied
 * @used_bytes: number of occupied bytes used
*/
typedef struct block_head
{
	size_t total_bytes;
	size_t used_bytes;
} blockhead;

/*Prototypes*/
void *naive_malloc(size_t size);
void *_malloc(size_t size);
void _free(void *ptr);

#endif
