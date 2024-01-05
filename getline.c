#include "shell.h"

/**
 * input_buf - Reads chained commands with buffers.
 * @info: Variable struct.
 * @buf: Buffer's address.
 * @len: Address for Len Var.
 *
 * Return: Read bytes.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif

		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0'; /* Remove the trailing newline */
				s--;
			}

			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			/* Check if it's a command chain */
			if (_strchr(*buf, ';'))
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}

	return (s);
}

/**
 * get_input - Eliminates the newline from a line.
 * @info: Variable struct.
 *
 * Return: Read bytes.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);

	if (r == -1) /* EOF */
		return (-1);

	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);

		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Reads a buffer.
 * @info: Variable struct.
 * @buf: The buffer.
 * @i: Size.
 *
 * Return: Read bytes.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);

	s = read(info->readfd, buf, READ_BUF_SIZE);

	if (s >= 0)
		*i = s;

	return (s);
}

/**
 * _getline - Obtains the following line of input from STDIN.
 * @info: Variable struct.
 * @ptr: Address of a buffer pointer that is preallocated or NULL.
 * @length: If not NULL, the size of the preallocated ptr buffer.
 *
 * Return: Read bytes.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;

	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);

	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;

	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Ctrl-C handler.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
