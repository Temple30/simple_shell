#include "shell.h"

/**
 * hsh - The main shell loop.
 * @info: The variable & return struct info.
 * @av: The vector argument from main().
 *
 * Return: 0 on success, otherwise error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t input_result = 0;
	int builtin_ret = 0;

	while (input_result != -1 && builtin_ret != -2)
	{
		clear_info(info);

		if (interactive(info))
			_puts("$ ");

		_eputchar(BUF_FLUSH);

		input_result = get_input(info);

		if (input_result != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);

			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
		{
			_putchar('\n');
		}

		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
	exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Finds a builtin command.
 * @info: The variable & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 for builtin executed successfully,
 *         1 for builtin found but not successful,
 *         2 for builtin signals exit().
 */
int find_builtin(info_t *info)
{
	int j, builtin_ret = -1;

	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
	{
		if (_strcmp(info->argv[0], builtintbl[j].type) == 0)
		{
			info->line_count++;
			builtin_ret = builtintbl[j].func(info);
			break;
		}
	}

	return (builtin_ret);
}

/**
 * find_cmd - Finds a command in PATH.
 * @info: The variable & return struct info.
 *
 * Return: void.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int j, k;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (j = 0, k = 0; info->arg[j]; j++)
	{
		if (!is_delim(info->arg[j], " \t\n"))
			k++;
	}

	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_cmd(info);
	} else
	{
		if ((interactive(info) || _getenv(info, "PATH=") ||
					info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			fork_cmd(info);
		} else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an exec thread to run a command.
 * @info: The variable & return info struct.
 *
 * Return: void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);

			if (errno == EACCES)
				exit(126);

			exit(1);
		}
	}
	else
	{
		wait(&(info->status));

		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
