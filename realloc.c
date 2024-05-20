#include "malloc.h"

/**
 * _realloc - reallocates memory & copies memory to new allocation
 * @ptr: pointer to memory for which space to be reallocated
 * @old_size: size of current allocation
 * @size: expected size of new memory allocation
 * Return: pointer to allocated memory, NULL upon allocation failure
 */
void *_realloc(void *ptr, size_t size);
void *_realloc(void *ptr, size_t old_size, size_t size)
{
	void *new_mem = NULL;

	if (!ptr)
	{
		new_mem = _malloc(size);
		if (!new_mem)
			return (NULL);
	}
	if (old_size < size)
	{
		new_mem = malloc(size);
		if (!new_mem)
			return (NULL);
		memcpy(new_mem, ptr, old_size);
		_free(ptr);
	}
	else
		new_mem = ptr;
	return (new_mem);
}