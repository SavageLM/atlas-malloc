#include "malloc.h"

void make_lock(void) __attribute__((constructor));
void break_lock(void) __attribute__((destructor));

pthread_mutex_t lock;

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

	pthread_mutex_lock(&lock);
	if (!nmemb || !size)
		return (NULL);
	memory = _malloc(nmemb * size);
	if (!memory)
		return (NULL);
	for (iter = 0, initialize = memory; iter != (size * nmemb); iter++)
		initialize[iter] = '\0';
	pthread_mutex_unlock(&lock);
	return (memory);
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
