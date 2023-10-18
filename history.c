#include "shell.h"

/**
 * get_history_file get history files
 * @info parameter struct
 * return allocated  str of historyfile
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;
	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) *(_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcoy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}


/**
 * write_history create || append to an existing file.
 * @info parameter structure
 * return onsucess (1) else (-1)
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if  (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	closed(fd);
	return (1);
}

/**
 * read_history reads hist from file.
 * @info parametere structure
 * return hist_count on success otherwise 0
 */
int read_history(info_t *info)
{
	int n, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!start(fd, &st))
		fsize = st st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close (fd);
	for (n = 0; n < fsize; n++)
		if (buf[n] == '\n')
		{
			buf[n]= 0;
			buid_history_list(info, buf + last, linecount++);
			last = n + 1;
		}
	if (last ! = n)
		buid_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * buid_history_list adds new entry to linkrx history list
 * @info struct containging potential arguments
 * @linecount history lincount
 * @buf buffer
 * return always 0
 */
int buid_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;
	if(info->history)
		node= info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history renumbers after changes the linkrd history files
 * @info  struct containing arguments
 * return new  histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int n =0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (info->histcount = n);
}
