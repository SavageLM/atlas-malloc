#include "malloc.h"

pthread_mutex_t lock;

/**
 * _free - Function to free a piece of memory
 * @ptr: pointer to block of memory to free
*/
void _free(void *ptr)
{
	blockhead *block;

	pthread_mutex_lock(&lock);
	if (ptr == NULL)
	{
		pthread_mutex_unlock(&lock);
		return;
	}
	/*Changes block data to show that memory is free to use*/
	block = (blockhead *)ptr;
	block--;
	block->used_bytes = 0;
	pthread_mutex_unlock(&lock);
}
