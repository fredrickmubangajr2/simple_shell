#include "shell.h"

/**
 * bfree - free pointer & the addess is NULL
 * @ptr: address of pointer freed
 * Return: if freed 1 otherwise 0
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
