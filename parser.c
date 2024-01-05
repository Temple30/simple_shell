#include "shell.h"

/**
 * is_cmd - Tests if a file is an executable command.
 * @info: Struct containing information.
 * @path: The file's location.
 *
 * Return: 1 if true, otherwise 0.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (S_ISREG(st.st_mode))
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Copies characters from a string with
 * specified start and stop indices.
 * @pathstr: The string path.
 * @start: Initial index.
 * @stop: Index for stopping.
 *
 * Return: A pointer to the new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int k = 0;
	int j;

	for (j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[k++] = pathstr[j];
	buf[k] = '\0';
	return (buf);
}

/**
 * find_path - Identifies the command in the PATH string.
 * @info: Struct containing information.
 * @pathstr: The string path.
 * @cmd: The command to locate.
 *
 * Return: Complete path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
