#include "malloc.h"

void make_lock(void) __attribute__((constructor));
void break_lock(void) __attribute__((destructor));

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

	block = (blockhead *)ptr;
	block--;
	block->used_bytes = 0;
	pthread_mutex_unlock(&lock);
}

/**
 * make_lock - Constructor for mutex lock
*/
void make_lock(void)
{
	pthread_mutex_init(&lock, NULL);
}

/**
 * break_lock - Destructor for mutex lock
*/
void break_lock(void)
{
	pthread_mutex_destroy(&lock);
}
