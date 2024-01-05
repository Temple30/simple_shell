#include "shell.h"
/**
* _interactive_mode - return true if the shell is in interactive mode
* @info: structure inforess
*
* Return: return 1 when in interactive mode, otherwise 0
*/
int _interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* _delimeter - check for character in delimeter
* @c: check character
* @delim_str: expected delimeter str
* Return: return 1 if expected is true, otherwise 0
*/
int _delimeter(char c, char *delim_str)
{
	while (*delim_str)
	{
		if (*delim_str++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
* _is_alpha - checks for alphabetic char
* @c: The char to be input
* Return: return 1 if c is alphabet, else 0
*/
int _is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
* _atoi - this convert a str to an int
* @s: the expected string that will be converted
* Return: return 0 if there is no numbers in the string,
* otherwise convert the number
*/
int _is_atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
		{
			sign *= -1;
		}
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
	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}
	return (output);
}

