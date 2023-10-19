#include "shell.h"

/**
 * list_len - determine linked list length
 * @h: first node pointer
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - return array str of list->str
 * @head: first node pointer
 * Return: array of str
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t n = list_len(head), k;
	char **strs;
	char *str;

	if (!head || !n)
		return (NULL);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < n; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[n] = str;
	}
	strs[n] = NULL;
	return (strs);
}

/**
 * print_list - prints elements of linke_d list_t list
 * @h: first node pointer
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar('');
		_putchr(h->str ? h->str : "(nil)");
		puts("\n")
			h = h->next;
		n++;
	}
	return (n);
}

/**
 * node_starts_with - returns node str start withprefix
 * @node: list head of pointer
 * @prefix: strto match
 * @c: next char after prefix to match
 * Return: match node || null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets index of a node
 * @node: node pointer
 * @head: list head pointer
 * Return: -1 || index node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}

