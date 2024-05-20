#include "malloc.h"

static heap_data heap = {NULL, NULL, 0, 0, 0};

/**
 * _malloc - Allocates memory in the heap
 * @size: size of memory to allocate
 * Return: returns a pointer to the allocated memory
*/

void *_malloc(size_t size)
{
	static int flag;
	size_t aligned_sz = ((size + 7) / 8) * 8;
	blockhead *ptr = NULL;

	if (!flag)
	{
		heap.first_block = sbrk(0);
		while (heap.heap_size < (aligned_sz + BLOCK_SZ))
		{
			sbrk(getpagesize());
			heap.heap_size += getpagesize(), heap.heap_free += getpagesize();
		}
		heap.first_block->total_bytes = aligned_sz;
		heap.first_block->used_bytes = aligned_sz;
		heap.heap_free = heap.heap_size - (BLOCK_SZ + aligned_sz);
		heap.numblock = 1;
		ptr = heap.first_block + 1;
		flag = 1;
		return ((void *) ptr);
	}
	while ((aligned_sz + BLOCK_SZ) > heap.heap_free)
	{
		sbrk(getpagesize());
		heap.heap_size += getpagesize(), heap.heap_free += getpagesize();
	}
	ptr = block_hopper((BLOCK_SZ + aligned_sz));
	heap.numblock++;
	heap.heap_free -= (BLOCK_SZ + aligned_sz);
	return ((void *) ++ptr);
}

/**
 * block_hopper - Function for traversing the header blocks
 * @size: Size user requests plus block header
 * Return: pointer to big enough chunk for size
*/
blockhead *block_hopper(size_t size)
{
	size_t i = 0, total = 0, used = 0;
	blockhead *pos;

	for (pos = heap.first_block; i < heap.numblock; i++)
	{
		if (pos->total_bytes >= size && !pos->used_bytes)
			return (pos);
		total = pos->total_bytes;
		used = pos->used_bytes;

		if (size <= (pos->total_bytes - pos->used_bytes))
		{
			/* pos->total_bytes = pos->used_bytes; */
			pos = (blockhead *)((char *)pos + sizeof(blockhead) + total);
			pos->total_bytes = total - used - BLOCK_SZ;
			pos->used_bytes = size - BLOCK_SZ;
			return (pos);
		}
		pos = (blockhead *)((char *)pos + sizeof(blockhead) + total);
	}
	pos->total_bytes = size - BLOCK_SZ;
	pos->used_bytes = size - BLOCK_SZ;
	return (pos);
}
