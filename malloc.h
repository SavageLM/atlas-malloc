#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * struct block_head
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
