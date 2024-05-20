#include "malloc.h"

/**
 * _calloc - allocates memory & initializes memory to 0 for array of objects
 *           of specified size
 * @nmemb: array object count for which memory to be allocated
 * @size: size of each array object
 * Return: pointer to allocated memory, NULL if either param is 0 or alloc fail
 */
void *_calloc(size_t nmemb, size_t size)
{
	void *memory = NULL;
	char *initialize = NULL;
	size_t iter = 0;

	if (!nmemb || !size)
		return (NULL);
	memory = malloc(nmemb * size);
	if (!memory)
		return (NULL);
	for (iter = 0, initialize = memory; iter != (size * nmemb); iter++)
		initialize[iter] = '\0';
	return (memory);
}
