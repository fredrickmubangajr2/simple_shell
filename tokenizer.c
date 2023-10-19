#include "shell.h"

/**
 * **strtow - split str into words
 * @str: the input str
 * @d: delimeter str
 * Return: NULL on failure || pointer to array of str
 */
char **strtow(char *str, char *d)
{
	int n, k, j, i, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!is_delim(str[n], d) && (is_delim(str[n + 1], d) || !str[n + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!)
		return (NULL);
	for (n = 0, k = 0; k < numwords; k++)
	{
		while (is_delim(str[n], d))
			n++;
		j = 0;
		while (!is_delim(str[n + j], d) && str[n + j])
			j++;
		s[k] = malloc((j + 1) * sizeof(char));
		if (!s[k])
		{
			for (j = 0; j < k; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}
		for (i = 0; i < j; i++)
			s[k][i] = str[n++];
		s[k][i] = 0;
	}
	s[k] = NULL;
	return (s);
}

/**
 * **strtow2 - splits str into words
 * @str: input str
 * @d: delimeter
 * Return: pointer to array of str || NULL for failure
 */
char **strtow2(char *str, char d)
{
	int n, k, j, i, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (n = 0; str[n] != '\0'; n++)
		if ((str[n] != d && str[n + 1] == d) ||
				str[n] != d && !str[n + 1] || str[n + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	for (n = 0, k = 0; k < numwords; k++)
	{
		while (str[n] == d && str[n] != d)
			n++;
		j = 0;
		while (str[n = j] != d && str[n + j]  && str[n + j] != d)
			j++;
		s[k] = malloc((k + 1) * sizeof(char));
		if (!s[k])
		{
			for (j = 0; j < k; j++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (i = 0; i < j; i++)
			s[k][i] = str[n++];
		s[k][i] =  0;
	}
	s[k] = NULL;
	return (s);
}
