#include "shell.h"

/**
 * input_buf buffers chained cmd
 * @info parameter structure
 * @buf address of buffer
 * @len address of len var
 * return bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, siginthandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info,  buf, &len_p);
#endif
		if (r > 0)
		{
			if  ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input gets a line minus the newline.
 * @info parameter structure
 * return  bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t n, k, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if(r == -1)
		return (-1);
	if(len)
	{
		k = n;
		p = buf + n;

		check_chain(info, buf, &k, n, len);
		while (k < len)
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		n = k + 1;
		if (n >= len)
		{
			n = len = 0;
			info->cnd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf reads buffer
 * @info parameter structure
 * @buf buffer
 * @n size
 * return r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *n)
{
	ssize_t r = 0;
	if(*n)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*n = r;
	return (r);
}

/**
 * _getline get next line of input from STDIN
 * @info parameter structure
 * @ptr address of pointer to buffer || NULL
 * @length size ptr buffer if not NULL
 * return s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t n, len;
	size_t j;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (n == len)
		n = len = 0;
	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + n, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s,  s ? s + j : j + 1);
	if (!new_P)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_P, buf + n, j - n);
	else
		_strncpy(new_P, buf + n, j - n + 1);

	s += j - n;
	n = j;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler block ctrl-C
 * @sig_num the signal num
 * return void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
				
