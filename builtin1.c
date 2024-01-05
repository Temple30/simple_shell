#include "shell.h"

/**
 * _exit_shell - exit  the shell
 * @info: this holds possible arguments which is Used to keep
 * continous function prototype.
 * Return: for info.argv[0] != "exit" specified exit status (0)
 */
int _exit_shell(info_t *info)
{
	int checkexit;

	if (info->argv[1]) /* If exit argument is available */
	{
		checkexit = _erratoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _current_dir - modification of the current working directory
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype
 * Return: 0 sucess
 */
int _current_dir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
		{
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		}
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: this should be what? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Unable to change directory ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _mod_cd - this modifications process's the current directory
 * @info: Structure with potential arguments
 * used to preserve the constant function prototype.
 * Return: 0 constant
 */
int _mod_cd(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function has not been implemented \n");
	if (0)
	{
		_puts(*arg_array); /* temp att_unused workaround */
	}
	return (0);
}

