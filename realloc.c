#include "shell.h"

/**
 * _memset - fill menory a constant byte
 * @s: pointer memory area
 * @m: ammount of byte to fill
 * @b: the byte to fill s with
 * Return: a pointer to memory area s
 */
char *_memset(char *s, char b, unsigned int m)
{
	unsigned int n;

	for (n = 0; n < m; n++)
		s[n] = b;
	return (s);
}

/**
 * ffree - frees str of str
 * @pp: str of str
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to prev mall block
 * @old_size: byte size of prev block
 * @new_size: byte size of new block
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size, new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
