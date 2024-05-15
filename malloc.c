#include "malloc.h"

heap_data heap;

/**
 * _malloc - Allocates memory in the heap
 * @size: size of memory to allocate
 * Return: returns a pointer to the allocated memory
*/

void *_malloc(size_t size)
{
	static int flag = 0;
	size_t aligned_sz = ((size + 7)/8) * 8;
	blockhead *ptr;

	if (!flag)
	{
		heap.first_block =sbrk(0);
		sbrk(getpagesize());
		heap.heap_size = getpagesize();
		heap.first_block->total_bytes = aligned_sz;
		heap.first_block->used_bytes = aligned_sz;
		heap.heap_free = heap.heap_size - aligned_sz;
		heap.numblock = 1;
		ptr = heap.first_block += 1;
		flag = 1;
		return ((void *) ptr);
	}
	if (heap.heap_free - aligned_sz < 1)
	{
		sbrk(getpagesize());
		heap.heap_size += getpagesize();
		heap.heap_free += getpagesize();
	}
	ptr = block_hopper((BLOCK_SZ + aligned_sz));
	ptr->total_bytes = aligned_sz;
	ptr->used_bytes = aligned_sz;
	ptr++;
	heap.numblock++;
	return ((void *)ptr);
}

/**
 * block_hopper - Function for traversing the header blocks
 * @size: Size user requests plus blcok header
 * Return: pointer to big enough chunk for size
*/
blockhead *block_hopper(size_t size)
{
	size_t i = 0;
	blockhead *pos;

	pos = heap.first_block;
	for (; i < heap.numblock; i++)
	{
		if (size < (pos->total_bytes - pos->used_bytes))
		{
			pos->total_bytes = pos->used_bytes;
			pos = (blockhead *)((char *)pos + sizeof(blockhead) + pos->total_bytes);
			return (pos);
		}
		pos = (blockhead *)((char *)pos + sizeof(blockhead) + pos->total_bytes);
	}
	return (pos);
}
