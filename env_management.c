#include "shell.h"

/**
 * _displayEnv - Display the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _displayEnv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _retrieveEnv - Retrieve the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *_retrieveEnv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _initializeEnv - Create or update an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _initializeEnv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _removeEnv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _removeEnv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * _populateEnvList - Populate the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _populateEnvList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
