#include "malloc.h"

static heap_data heap = {NULL, 0, 0, 0};

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
	while (heap.heap_free - (aligned_sz + BLOCK_SZ) < 1)
	{
		sbrk(getpagesize());
		heap.heap_size += getpagesize(), heap.heap_free += getpagesize();
	}
	/* ptr->total_bytes = aligned_sz; */
	/* ptr->used_bytes = aligned_sz; */
	ptr = block_hopper((BLOCK_SZ + aligned_sz));
	ptr++;
	heap.numblock++;
	heap.heap_free -= (BLOCK_SZ + aligned_sz);
	return ((void *)ptr);
}

/**
 * block_hopper - Function for traversing the header blocks
 * @size: Size user requests plus block header
 * Return: pointer to big enough chunk for size
*/
blockhead *block_hopper(size_t size)
{
	size_t i = 0, tmp1 = 0, tmp2 = 0;
	blockhead *pos;

	pos = heap.first_block;
	for (; i < heap.numblock; i++)
	{
		if (pos->total_bytes >= size && !pos->used_bytes)
			return (pos);
		if (size < (pos->total_bytes - pos->used_bytes))
		{
			tmp1 = pos->total_bytes;
			tmp2 = pos->used_bytes;
			/* pos->total_bytes = pos->used_bytes; */
			pos = (blockhead *)((char *)pos + sizeof(blockhead) + tmp1);
			pos->total_bytes = tmp1 - tmp2 - BLOCK_SZ;
			pos->used_bytes = size - BLOCK_SZ;
			return (pos);
		}
		pos = (blockhead *)((char *)pos + sizeof(blockhead) + pos->total_bytes);
	}
	pos->total_bytes = size - BLOCK_SZ;
	pos->used_bytes = size - BLOCK_SZ;
	return (pos);
}
