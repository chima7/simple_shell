#include "shell.h"

/**
 * get_list_length - Calculate the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Length of the list.
 */
size_t get_list_length(const list_t *head)
{
	size_t length = 0;
	const list_t *current = head;

	while (current != NULL)
	{
		length++;
		current = current->next;
	}
	return (length);
}

/**
 * convert_list_to_strings - Transform a string-linked list into a string array
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **convert_list_to_strings(list_t *head)
{
	size_t length = get_list_length(head);
	char **str_array = malloc((length + 1) * sizeof(char *));
	size_t i = 0;

	if (str_array == NULL)
		return (NULL);

	list_t *current = head;

	while (current != NULL)
	{
		str_array[i] = strdup(current->str);
		if (str_array[i] == NULL)
		{
			for (size_t j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}
		current = current->next;
		i++;
	}

	str_array[length] = NULL;
	return (str_array);
}

/**
 * print_list_nodes - Print all elements of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list_nodes(const list_t *head)
{
	size_t count = 0;
	const list_t *current = head;

	while (current != NULL)
	{
		printf("%ld: %s\n", current->num, current->str ? current->str : "(nil)");
		current = current->next;
		count++;
	}
	return (count);

}

/**
 * find_node_starts_with - Find a node whose string starts with a prefix.
 * @head: Pointer to the list head.
 * @prefix: Prefix to match.
 * @c: The next character after prefix to match.
 *
 * Return: Matching node or NULL.
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char c)
{
	list_t *current = head;

	while (current != NULL)
	{
		if (starts_with(curr->str, pre) && (c == -1 || starts_with(curr->str + strlen(pre), &c)))
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * get_node_index - Get the index of a specific node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;
	list_t *current = head;

	while (current != NULL)
	{
		if (current == node)
			return (index);
		current = current->next;
		index++;
	}
	return (-1);
}

