#include "shell.h"

/**
 * _myhistory - displays history  list '\n' starting at 0
 * @info: sturecture containing pontential arguments
 * Return: always (0)
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - set alias to strings.
 * @str: the string alias
 * @info: parameter struct
 * Return: always (0) when successful otherwise (1) on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - alias to string
 * @str: string alias
 * @info: parameter struct
 * Return: always (0) if sucessful otherwise (1) on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');

	if (!)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string.
 * @node: alias node.
 * Return: always (0) if suceesful otherwise 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');

	for (a = node->str; a <= p; a++)

		_putchar(*a);
		_putchar('\');
		_puts(p + 1);
		_puts('\n');
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int n = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;

		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (n = 1; info->argv[n]; n++)
	{
		p = _strchr(info->argv[n], "=");
		if (p)
			set_alias(info, info->argv[n]);
		else
			print_alias(node_starts_with(info->alias, info->argv[n], "="));
	}
	return (0);
}
