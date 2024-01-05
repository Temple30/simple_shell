#include "shell.h"

/**
 * bfree - Releases a pointer and sets the address to NULL.
 * @ptr: The pointer's address to free.
 *
 * Return: 1 if successfully freed, 0 otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
