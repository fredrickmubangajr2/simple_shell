#include "shell.h"

/**
 * _eputs - prints input string
 * @str: string to be printed
 * Return nothing
 */
void_eputs(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_eputchar(str[n]);
		n++;
	}
}

/**
 * _eputchar - writes char c to stderr
 * @c: char to print
 * Return: 1 on sucess.therwise -1 on error, errno is set appropriately.
 */
int _eputchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buff[n++] = c;
	return (1);
}

/**
 * _putfd - write char c to fd
 * @c: char to print
 * @fd: filedescriptor
 * Return: 1 on sucess, -1 on error, errno set appropriately
 */
int _putfd(char c, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * _putsfd - printsinput string
 * @str: printed string
 * @fd: filedescriptor
 * Return: num of chars.
 */
int _putsfd(char *str, int fd)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += _putfd(*str++, fd);
	}
	return (n);
}
