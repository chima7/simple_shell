#include "shell.h"

/**
 * get_history_file - Get the path of the history file.
 * @info: Parameter structure.
 * Return: Allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
	char *dir = _getenv(info, "HOME=");

	if (!dir)
		return (NULL);

	char *buf = malloc(_strlen(dir) + _strlen(HIST_FILE) + 2);

	if (!buf)
	{
		free(dir);
		return (NULL);
	}

	snprintf(buf, _strlen(dir) + _strlen(HIST_FILE) + 2, "%s/%s", dir, HIST_FILE);
	free(dir);
	return (buf);
}

/**
 * write_history - Write the history to a file.
 * @info: Parameter structure.
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
		return (-1);

	FILE *file = fopen(filename, "w");

	free(filename);

	if (!file)
		return (-1);


	list_t *node = info->history;

	while (node)
	{
		fprintf(file, "%s\n", node->str);
		node = node->next;
	}

	fclose(file);
	return (1);
}

/**
 * read_history - Read the history from a file.
 * @info: Parameter structure.
 * Return: Histcount on success, 0 on failure.
 */
int read_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
		return (0);

	FILE *file = fopen(filename, "r");

	free(filename);

	if (!file)
		return (0);

	char *line = NULL;
	size_t len = 0;
	int linecount = 0;

	while (getline(&line, &len, file) != -1)
	{
		line[strcspn(line, "\n")] = '\0';
		build_history_list(info, line, linecount++);
	}

	free(line);
	fclose(file);

	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Build a history linked list by adding an entry.
 * @info: Parameter structure.
 * @buf: Buffer.
 * @linecount: History linecount, histcount.
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: Parameter structure.
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}
