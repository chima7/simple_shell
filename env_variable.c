#include "shell.h"

/**
 * get_environment - Returns the string array copy of our environment.
 * @info: Structure containing potential arguments.
 * Return: String array containing environment variables.
 */

char **get_environment(info_t *info);
int remove_environment_variable(info_t *info, char *variable);
int set_environment_variable(info_t *info, char *variable, char *value);

char **get_environment(info_t *info)
{
	if (!info->environment || info->env_changed)
	{
		info->environment = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environment);
}

/**
 * remove_environment_variable - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @variable: The string env variable to be removed.
 * Return: 1 on successful deletion, 0 otherwise.
 */

int remove_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_environment_variable - Create or update an environment variable.
 * @info: Structure containing potential arguments.
 * @variable: The string env variable.
 * @value: The string env variable value.
 * Return: Always 0.
 */

int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buf = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, variable);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, variable);
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
