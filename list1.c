#include "shell.h"

/**
* _my_list_len - specification of the link list
* @h: pointer of the first node
*
* Return: sixe of the list
*/
size_t _my_list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
* shell_list_to_strings - returns an array of strings
* using the list->str method.
* @head: pointer of first node
*
* Return: array in string
*/
char **shell_list_to_strings(list_t *head)
{
	size_t i = list_len(head), j;
	list_t *node = head;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
* print_list - prints every element of a list_t linked list.
* @h: pointer of first node
*
* Return: the list size
*/
size_t print_my_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
* node_starts_point - provides a node whose
* string contains the prefix.
* @node: list head pointer
* @prefix: matching string
* @c: the character following prefix that will match
*
* Return: null of match nodes
*/
list_t *node_starts_point(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
* get_node_index - obtaining index of node
* @head: list head pointer
* @node: pointer to the node
*
* Return: zero or the node's index
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}

