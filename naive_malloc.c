#include "malloc.h"

static heap_data heap = {NULL, NULL, 0, 0, 0};

/**
 * naive_malloc - Allocates memory in the heap
 * @size: size of memory to allocate
 * Return: returns a pointer to the allocated memory
*/

void *naive_malloc(size_t size)
{
	static int flag;
	size_t aligned_sz = ((size + 7) / 8) * 8;
	naiveblock *ptr = NULL;

	/*On First call of function sets up data struct and initializes the heap*/
	if (!flag)
	{
		heap.naive_block = sbrk(0);
		while (heap.heap_size < (aligned_sz + NAIVEBLOCK_SZ))
		{
			/*Sets end of heap address*/
			sbrk(getpagesize());
			heap.heap_size += getpagesize(), heap.heap_free += getpagesize();
		}
		/*Sets members of data struct*/
		heap.naive_block->total_bytes = aligned_sz;
		heap.heap_free = heap.heap_size - (NAIVEBLOCK_SZ + aligned_sz);
		heap.numblock = 1;
		ptr = heap.naive_block + 1;
		flag = 1;
		return ((void *) ptr);
	}
	/*When not enough free memory, allocates more*/
	while (heap.heap_free - (aligned_sz + NAIVEBLOCK_SZ) < 1)
	{
		sbrk(getpagesize());
		heap.heap_size += getpagesize(), heap.heap_free += getpagesize();
	}
	/*Traversing Header Blocks and adjusting data structs*/
	ptr = naive_hopper((NAIVEBLOCK_SZ + aligned_sz));
	heap.numblock++;
	heap.heap_free -= (NAIVEBLOCK_SZ + aligned_sz);
	return ((void *) ++ptr);
}

/**
 * naive_hopper - Function for traversing the header blocks
 * @size: Size user requests plus block header
 * Return: pointer to big enough chunk for size
*/
naiveblock *naive_hopper(size_t size)
{
	size_t i = 0, total = 0;
	naiveblock *pos;

	pos = heap.naive_block;
	/*Moves position based on meta data in block header*/
	for (; i < heap.numblock; i++)
	{
		total = pos->total_bytes;
		/*Typecasting to get accurate pointer movement*/
		pos = (naiveblock *)((char *)pos + sizeof(naiveblock) + total);
	}
	pos->total_bytes = size - NAIVEBLOCK_SZ;
	return (pos);
}
