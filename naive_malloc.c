#include "malloc.h"

void *naive_malloc(size_t size);

static size_t allocated;

/**
 * naive_malloc - naive variant of custom malloc implementation
 * @size: size in bytes of memory to be allocated
 * Return: pointer to suitably aligned allocated memory
*/
void *naive_malloc(size_t size)
{
	void *prev_break;

	sbrk(0);
	prev_break = sbrk(size);
	if (prev_break == (void *) -1)
		return (NULL);
	allocated += size;
	return (prev_break);
}
