#include "malloc.h"

struct heap_data heap;

/**
 * _malloc - Allocates memory in the heap
 * @size: size of memory to allocate
 * Return: returns a pointer to the allocated memory
*/

void *_malloc(size_t size)
{
	static int flag = 0;
	size_t ptr;

	if (!flag)
	{
		heap.first_block =sbrk(0);
		sbrk(getpagesize());
		heap.heap_size = getpagesize();
		heap.numblock = 1;
		ptr += 17;
		flag = 1;
		return ((void *) ptr);
	}

	/*Allocate to memory*/
	
}