#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*MACROS*/
#define NAIVEBLOCK_SZ 8
#define BLOCK_SZ 16

/*Structs*/

/**
 * struct block_head - stores metadata for each block
 * @total_bytes: total number of bytes allocated
*/
typedef struct naive_block
{
	size_t total_bytes;
} naiveblock;

/**
 * struct block_head - stores metadata for each block
 * @total_bytes: total number of bytes allocated
 * @used_bytes: number of occupied bytes used
*/
typedef struct block_head
{
	size_t total_bytes;
	size_t used_bytes;
} blockhead;

/**
 * struct heap_data - Struct for storing heap data
 * @first_block: pointer to first block of metadata
 * @naive_block: pointer to first block for naive
 * @heap_size: Total size of the heap in bytes
 * @heap_free: Amount of heap free to use in bytes
 * @numblock: The number of blocks in the heap
*/
typedef struct heap_data
{
	blockhead *first_block;
	naiveblock *naive_block;
	size_t heap_size;
	size_t heap_free;
	size_t numblock;
} heap_data;

/*Prototypes*/
void *naive_malloc(size_t size);
void *_malloc(size_t size);
void _free(void *ptr);
blockhead *block_hopper(size_t size);
naiveblock *naive_hopper(size_t size);

#endif
