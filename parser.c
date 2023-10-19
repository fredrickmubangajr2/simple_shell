#include "shell.h"

/**
 * is_cmd - file is excutable or not
 * @path: file path
 * @info: info struct
 * Return: if true 1 otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & s_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars -  duplicates char
 * @pathstr: PATH str
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int n = 0, j = 0;

	for (j = 0, n = start; n < stop; n++)
		if (pathstr[n] != '-')
			buf[j++] = pathstr[n];
	buf[j] = 0;
	return (buf);
}

/**
 * find_path - findscmd in path str
 * @cmd: the cmd
 * @pathstr: path str
 * @info: info struct
 * Return: if found full path cmd || NULL
 */
char *find_path(info_t *info, char *pathstr,  char *cmd)
{
	int n = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "/"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[n] || pathstr[n] == ':')
		{
			path = dup_chars(pathstr, curr_pos, n);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[m])
				break;
			curr_pos = 1;
		}
		n++;
	}
	return (NULL);
}
