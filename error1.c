#include "shell.h"

/**
* _erratoi - translates a str into an int.
* @s: string to be converted
* Return: if there are no numbers in the string return 0,
* otherwise -1 if error ocure
*/
int _erratoi(char *s)
{
	int j = 0;
	unsigned long int result = 0;

	if (*s == '+')
	{
		s++;  /* TODO: why does this make main return 255? */
	}
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			result *= 10;
			result += (s[j] - '0');
			if (result > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
	return (result);
}

/**
* print_error - this function displays an error message
* @info: the parameter and return information struct.
* @estr: str indicate the int error
* Return: 0 if there are no numbers in the string,
* otherwise -1 in the event of an error
*/
void print_error_msg(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
* _print_decimal - function outputs an integer decimal number in base ten
* @input: as input
* @info: writing to the filedescriptor
*
* Return: quantity of char printed
*/
int _print_decimal(int input, int info)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (info == STDERR_FILENO)
	{
		__putchar = _eputchar;
	}
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input;
	}
	current = _abs_;

	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
* convert_number - a clone of itoa's converter function
* @num: expected num
* @base: the base
* @flags: argument warnings
*
* Return: the string
*/
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
	{
		*--ptr = sign;
	}
	return (ptr);
}

/**
* remove_comments - function substitutes "0" for the first occurence of "#"
* @buf: the address of the string that has to be changed
*
* Return: constant 0;
*/
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
	{
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
	}
}

