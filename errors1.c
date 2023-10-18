#include "shell.h"

/**
 * _erratoi converts a str to an int
 * @s str to be converted to int
 * return 0 no num in str || -1 on error
 */
int_erratoi(char *s)
{
	int n = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (n = 0; s[n] != '\0'; n++)
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			result *= 10;
			result += (s[n] = '0');
			if (result > INT_MAX)
				return  (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error outputs an error massage
 * @info parameter and return info struct
 * @estr strcontaining types of error
 * return no num in str (0)
 * otherwise -1 on error
 */
void print_error(info_t, char *estr)
{
	_eputs(info->fname);
	_eputs(":");
	print_d(infp->line_count, STDERR_FILENO);
	_eputs(":");
	_puts(info->argv[0]);
	_eputs(":");
	_eputs(estr);
}

/**
 * print_d prints an int in base10
 * @input input
 * @fd filedescriptor
 * return num of char printed.
 */
int print_d(int input,int fd)
{
	int(*_putchar)(char) = _putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FELINO)
		_putchar = _putchar;
	if (input < 0)
	{
		_abs_ = -input;
		_putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (n = 1000000000; n > 1; n/= 10)
	{
		if (_abs_/n)
		{
			_putchar('0'  + current/n);
			count++;
		}
		current %= n;
	}
	_putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number conveter function from itoa clone.
 * @num number
 * @flags aguement flag
 * @base base
 * return string
 */
cha *convert_number(long int num, int base, int flags)
{
	static char *arrays;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long m = num;

	if(!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		m = num;
		sign = '-';
	}
	array = flags &  CONVERT_LOWERCASE? "0123456789abdef" :
		"0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[m % base];
		m /= base;
	}
	while (m != 0);

	if  (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments function replace '#' to '\0'
 * @buf address of modify string
 * return always (0);
 */
void remove_comments(char *buf)
{
	int n;

	for (n = 0; buf[n] != '\0'; n++)
		if (buf[n] == '#' && (!n || buf[n - 1] == ''))
		{
			buf[n] ='\0';
			break;
		}
}
