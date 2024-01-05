#include "shell.h"

/**
* _get_file_history - history file to find
* @info: variable struct
*
* Return: string containing a history file
*/

char *_get_file_history(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
	{
		return (NULL);
	}
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
* write_to_history - appends to an existing file if file exisr
* or generates a new one if not exist
* @info: variable struct
*
* Return: 1 sucess else -1 if fail
*/
int write_to_history(info_t *info)
{
	ssize_t input;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
	{
		return (-1);
	}

	input = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (input == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, input);
		_putfd('\n', input);
	}
	_putfd(BUF_FLUSH, input);
	close(input);
	return (1);
}

/**
* read_file_history - file history to be read
* @info: this is the variable struct
*
* Return: if successful, history count; otherwise, 0
*/
int read_file_history(info_t *info)
{
	int j, last = 0, linecount = 0;
	ssize_t input, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	input = open(filename, O_RDONLY);
	free(filename);
	if (input == -1)
		return (0);
	if (!fstat(input, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(input, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(input);
	for (j = 0; j < fsize; j++)
	{
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + last, linecount++);
			last = j + 1;
		}
	}
	if (last != j)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
* build_history_list - creates a new entry in a history-linked list
* @info: Potential argument-containing structure is employed
* to keep the constant function prototype.
* @buf: buffer
* @linecount: history linecount and history count
*
* Return: constant 0
*/
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
* renumber_history - the history linked list
* is renumbered as modifications are made.
* @info: Potential argument-containing structure is employed
* to keep the constant function prototype.
* Return: the new histcount
*/
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}

