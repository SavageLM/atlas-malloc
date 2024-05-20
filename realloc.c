#include "malloc.h"

pthread_mutex_t lock;

/**
 * _realloc - reallocates memory & copies memory to new allocation
 * @ptr: pointer to memory for which space to be reallocated
 * @size: expected size of new memory allocation
 * Return: pointer to allocated memory, NULL upon allocation failure
 */
void *_realloc(void *ptr, size_t size)
{
	void *new_mem = NULL;
	size_t old_size = 0;

	pthread_mutex_lock(&lock);
	if (!size)
	{
		_free(ptr);
		pthread_mutex_unlock(&lock);
		return (NULL);
	}
	if (!ptr)
	{
		new_mem = _malloc(size);
		if (!new_mem)
		{
			pthread_mutex_unlock(&lock);
			return (NULL);
		}
	}
	else
	{
		old_size = (((blockhead *)ptr) - 1)->used_bytes;
		if (old_size < size)
		{
			new_mem = _malloc(size);
			if (!new_mem)
			{
				pthread_mutex_unlock(&lock);
				return (NULL);
			}
			memcpy(new_mem, ptr, old_size);
			_free(ptr);
		}
		else
			new_mem = ptr;
	}
	pthread_mutex_unlock(&lock);
	return (new_mem);
}
