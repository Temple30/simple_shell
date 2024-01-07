#include "shell.h"

/**
 * _myhistory - shows the history list, one command per line,
 * with line numbers starting at 0 before each command.
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype
 *  Return: constant 0.
 */
int _myhistory(info_t *info)
{
        print_list(info->history);
        return (0);
}

/**
 * unset_alias - changes alias to a string
 * @info: variable struct
 * @str: aliasing the string
 *
 * Return: 0 always on success and 1 for failure
 */
int unset_alias(info_t *info, char *str)
{
        char *p, c;
        int ret;

        p = _strchr(str, '=');
        if (!p)
                return (1);
        c = *p;
        *p = 0;
        ret = delete_node_at_index(&(info->alias),
                get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
        *p = c;
        return (ret);
}

/**
 * set_alias - changes alias to a string
 * @info: variable struct
 * @str: aliasing the string
 *
 * Return:  0 always on success and 1 for failure
 */
int set_alias(info_t *info, char *str)
{
        char *p;

        p = _strchr(str, '=');
        if (!p)
                return (1);
        if (!*++p)
                return (unset_alias(info, str));

        unset_alias(info, str);
        return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - displays an alias string.
 * @node: an alias node
 *
 * Return: 0 always on success and 1 for failure
 */
int print_alias(list_t *node)
{
        char *p = NULL, *a = NULL;

        if (node)
        {
                p = _strchr(node->str, '=');
                for (a = node->str; a <= p; a++)
                _putchar(*a);
                _putchar('\'');
                _puts(p + 1);
                _puts("'\n");
                return (0);
        }
        return (1);
}

/**
 * _myalias - imitates the built-in alias (man alias)
 * @info: Potential argument-containing structure is employed
 * to keep the constant function prototype.
 *  Return: constant 0
 */
int _myalias(info_t *info)
{
        int j = 0;
        char *p = NULL;
        list_t *node = NULL;

        if (info->argc == 1)
        {
                node = info->alias;
                while (node)
                {
                        print_alias(node);
                        node = node->next;
                }
                return (0);
        }
        for (j = 1; info->argv[j]; j++)
        {
                p = _strchr(info->argv[j], '=');
                if (p)
                        set_alias(info, info->argv[j]);
                else
                        print_alias(node_starts_with(info->alias, info->argv[j], '='));
        }

        return (0);
}
