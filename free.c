#include "malloc.h"
#include "malloc.c"

/**
 * _free - Function to free a piece of memory
 * @ptr: pointer to block of memory to free
*/
void _free(void *ptr)
{
	blockhead *block;

	block = (blockhead *)ptr;
	block->used_bytes = 0;
}
