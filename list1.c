#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}

	return count;
}

/**
 * list_to_strings - Converts a linked list to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t size = list_len(head);
	char **strs;
	char *str;
	size_t i, j;

	if (!head || size == 0)
		return NULL;

	strs = malloc(sizeof(char *) * (size + 1));
	if (!strs)
		return NULL;

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return NULL;
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return strs;
}

/**
 * print_list - Prints every element of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return count;
}

/**
 * node_starts_with - Finds a node whose string contains the given prefix.
 * @node: Pointer to the head of the list.
 * @prefix: String to match as a prefix.
 * @c: The character following the prefix that will match.
 *
 * Return: Pointer to the matching node or NULL if no match is found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return node;
		node = node->next;
	}

	return NULL;
}

/**
 * get_node_index - Obtains the index of a node in a linked list.
 * @head: Pointer to the head of the list.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;

		head = head->next;
		index++;
	}

	return -1;
}

