#include "shell.h"

/**
 * _eputs - Prints a string to stderr
 * @str: String to be printed
 *
 * Return: void
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;

	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - Updates stderr with the character 'c'
 * @c: Character to be printed
 *
 * Return: 1 on success, -1 on failure
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
		buf[j++] = c;

	return 1;
}

/**
 * _putfd - Puts a character 'c' in the supplied file descriptor 'fd'
 * @c: Character to be printed
 * @fd: File descriptor to write to
 *
 * Return: 1 on success, -1 on failure
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}

	if (c != BUF_FLUSH)
		buf[j++] = c;

	return 1;
}

/**
 * _putsfd - Displays a string to the specified file descriptor 'fd'
 * @str: String to be printed
 * @fd: File descriptor to write to
 *
 * Return: Number of characters written
 */
int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return 0;

	while (*str)
	{
		j += _putfd(*str++, fd);
	}

	return j;
}

