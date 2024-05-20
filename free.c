#include "malloc.h"

/**
 * _free - Function to free a piece of memory
 * @ptr: pointer to block of memory to free
*/
void _free(void *ptr)
{
	blockhead *block;

	if (ptr == NULL)
		return;

	block = (blockhead *)ptr;
	block--;
	block->used_bytes = 0;
}
