#include "shell.h"

/**
 * is_chain - test if current char in buffer a chain delimeter
 * @info: paremeter struct
 * @p: address currentposition
 * @buf: char buffer
 * Return: if chain delimiter 1, othewise 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * check_chain - checks the continued chaining based on last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: address current position in buf
 * @n: start position in buf
 * @len: length of buf
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t n, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[n] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[n] = 0;
			k = len;
		}
	}
	*p = k;
}

/**
 * replace_alias - replace aliases in tokenized str
 * @info: parameter struct
 * Return: if replaced 1 othewuse 0
 */
int replace_alias(info_t *info)
{
	int n;
	list_t *node;
	char *p;

	for (n = 0; n < 10; n++)
	{
		node =  node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p =  _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replace vars in the tokenized str
 * @info: parameter structure
 * Return: ifreplaced 1 otherwise 0
 */
int replace_vars(info_t *info)
{
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] != '$' || !info->argv[n][1])
			continue;

		if (!_strcmp(info->argv[n], "$?"))
		{
			replace_string(&(info->argv[n]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[n], "$$"))
		{
			replace_string(&(info->argv[n],
						_strdup(convert_number(getpid(), 10, 0))));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[n][1], '=');
		if (node)
		{
			replace_string(&(info->argv[n],
						_strdup(_strchr(node->str, '=') + 1)));
			continue;
		}
		replace_string(&info->argv[n], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replace string
 * @old: address of old str
 * @new: new str
 * Return: if replaced 1 otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
