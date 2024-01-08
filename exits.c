#include "shell.h"

/**
 * _strncpy - Duplicates a string up to a specified number of characters.
 * @dest: The destination string to copy to.
 * @src: The original string to copy.
 * @n: The number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j;

	char *s = dest;

	for (j = 0; src[j] != '\0' && j < n - 1; j++)
	{
		dest[j] = src[j];
	}

	while (j < n)
	{
		dest[j++] = '\0';
	}

	return (s);
}

/**
 * _strncat - Concatenates two strings up to a specified number of characters.
 * @dest: The initial string.
 * @src: The second string to concatenate.
 * @n: The maximum number of characters to use from src.
 *
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int j, k;

	char *s = dest;

	for (j = 0; dest[j] != '\0'; j++)
	{
	}

	for (k = 0; src[k] != '\0' && k < n; j++, k++)
	{
		dest[j] = src[k];
	}

	if (k < n)
	{
		dest[j] = '\0';
	}

	return (s);
}

/**
 * _strchr - Finds a character within a string.
 * @s: The string to search.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}

