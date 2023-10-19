#include "shell.h"

/**
 * _myenv - prints current environ
 * @info: sture containing potential arguments
 * Return: always (0)
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets value in environ variables.
 * @info: structure containing potential arguments
 * @name: enviroment variable name
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node + node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - new enviroment variable initialize
 * @info: structure containing potential arguments
 * Return: always (0)
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove enviroment variable.
 * @info: structure
 * @info_t: containing potetial arguments.
 * Return: always (0)
 */
int _myunsetenv(info_t, *info)
{
	int n;

	if (info->argc == 1)
	{
		_eputs("too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
		unsetenv(info, info->argv[n]);
	return (0);
}

/**
 * populate_env_list - populate env linked list
 * @info: structure containing potential arguments
 * Return: always (0)
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&node, environ[n], 0);
	info->env = node;
	return (0);
}
