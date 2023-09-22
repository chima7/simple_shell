#include "shell.h"

/**
 * list_length - Determine the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_str_array - Convert a linked list of strings to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_str_array(list_t *head)
{
	list_t *node = head;
	size_t len = list_length(head), i;
	char **str_arr;
	char *str;

	if (!head || !len)
		return (NULL);

	str_arr = malloc(sizeof(char *) * (len + 1));
	if (!str_arr)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (; i > 0; i--)
				free(str_arr[i - 1]);
			free(str_arr);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_arr[i] = str;
	}
	str_arr[i] = NULL;
	return (str_arr);
}

/**
 * print_linked_list - Print all elements of a linked list of strings.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_linked_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with_prefix - Return a node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @next_char: The next character after the prefix to match.
 *
 * Return: Matched node or NULL.
 */
list_t *node_starts_with_prefix(list_t *node, char *prefix, char next_char)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((next_char == -1) || (*p == next_char)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index_by_pointer - Get the index of a node by its pointer.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1.
 */
ssize_t get_node_index_by_pointer(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
