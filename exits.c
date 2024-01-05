#include "shell.h"

/**
**_str_cpy - copy a string
*@dest: copied string to it final destination
*@src: actual string
*@n: number of character to be copied
*Return: copied string
*/
char *_str_cpy(char *dest, char *src, int n)
{
	int j;
	int i;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		i = j;
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (s);
}

/**
**_str_cat - double string are copied
*@dest: actual string
*@src: other string
*@n: the maximum number of bytes to be used
*Return: concatenated string
*/
char *_str_cat(char *dest, char *src, int n)
{
	int j, i;
	char *s = dest;

	j = 0;
	i = 0;
	while (dest[j] != '\0')
	{
		j++;
	}
	while (src[i] != '\0' && i < n)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	if (i < n)
	{
		dest[j] = '\0';
	}
	return (s);
}

/**
**_str_chr - finds a character in a string
*@s: string that has to be parsed
*@c: char to looi for
*Return: a pointer to the memory location s
*/
char *_str_chr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}

