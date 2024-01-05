#include "shell.h"

/**
* add_node - put a node at the beginning of the list.l
* @head: node head pointer address
* @str: str field for node
* @num: used by history as a node index
*
* Return: size list
*/
list_t *add_a_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
	{
		return (NULL);
	}
	new_head = malloc(sizeof(list_t));
	if (!new_head)
	{
		return (NULL);
	}
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
* add_node_at_end - add a node at the end of a list.l.
* @head: the head node's pointer address
* @str: field for node str
* @num: using history's node index
*
* Return: list size
*/
list_t *add_node_at_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
	{
		return (NULL);
	}

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
* print_list_str - print only the str element from a linked list using list_t
* @h: first pointer node
*
* Return: list size
*/
size_t print_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
* erase_node_at_index - erase a node at a specified index.
* @head: the actual node's address of the pointer
* @index: index of the node to remove
*
* Return: 1 if suceed else 0 if fail
*/
int erase_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
	{
		return (0);
	}

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
* free_a_list - free all nodes of a list
* @head_ptr: address of a pointer head
*
* Return: void
*/
void free_a_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
	{
		return;
	}
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

