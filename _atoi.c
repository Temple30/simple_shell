#include "shell.h"

/**
 * interactive - Check if the shell is in interactive mode
 * @info: Pointer to the info_t structure
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Check if a character is a delimiter
 * @c: Character to be checked
 * @delim: Delimiter string
 *
 * Return: 1 if true, 0 otherwise
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - Check if a character is alphabetic
 * @c: The character to be checked
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - Convert a string to an integer
 * @s: The string to be converted
 *
 * Return: 0 if there are no numbers in the
 * string, otherwise the converted number
 */
int _atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[j] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	output = (sign == -1) ? -result : result;

	return (output);
}
