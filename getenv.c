#include "shell.h"

/**
* get_environment - return s copy of the environment string.
* @info: Potential argument-containing structure is employed
* to keep the constant function prototype.
* Return: 0 (constant)
*/
char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
* _undefine_environment - Erase an environment variable
* @info: Potential argument-containing structure is employed
* to keep the constant function prototype.
* Return: removed result is 1, else 0
* @var: environment variable property for strings
*/
int _undefine_environment(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *p;

	if (!node || !var)
	{
		return (0);
	}
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
* _define_environment - This function create a new environment
* variable from scratch, or alter one that already exists
* @info: Potential argument-containing structure. is employed
* to keep the constant function prototype.
* @var: environment variable property for strings
* @value: the environment variable value string
*  Return: 0 (constant)
*/
int _define_environment(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
	{
		return (0);
	}
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
	{
		return (1);
	}
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

