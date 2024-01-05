#include "shell.h"

/**
* _eputs_str - prints a string from usser input
* @str: string that will be printed
*
* Return: 0 Always sucess.
*/
void _eputs_str(char *str)
{
	int j = 0;

	if (!str)
	{
		return;
	}
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
* _eputchar - updated with the char c with stddr
* @c: Printing the char
*
* Return: 1 if suceed else -1 if fail,
* and the appropriate value of erro is set.
*/
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[j++] = c;
	}
	return (1);
}

/**
* _putfd - puts a char c in the supplied input
* @c: Printing the char
* @input: The address to write to
*
* Return: 1 is returned upon success, -1 upon failure,
* and the appropriate value of erro is set.
*/
int _putfd(char c, int input)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(input, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[j++] = c;
	}
	return (1);
}

/**
* _putsfd - prints a string of input
* @str: string that will be printed
* @input: The address to be written to
*
* Return: the total of character entered
*/
int _putsfd(char *str, int input)
{
	int j = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		j += _putfd(*str++, input);
	}
	return (j);
}

