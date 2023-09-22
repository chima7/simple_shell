#include "shell.h"

/**
 * exit_shell - Exit the shell.
 * @info: Structure containing potential arguments.
 * Return: Exits the shell with the specified exit status.
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Invalid exit code: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_status;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Change the current directory.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int change_directory(info_t *info)
{
	char *current_path, *new_path, buffer[1024];
	int chdir_ret;

	current_path = getcwd(buffer, 1024);
	if (!current_path)
		_puts("TODO: Handle getcwd failure here\n");
	if (!info->argv[1])
	{
		new_path = _getenv(info, "HOME=");
		if (!new_path)
			chdir_ret = /* TODO: Handle this case */
				chdir((new_path = _getenv(info, "PWD=")) ? new_path : "/");
		else
			chdir_ret = chdir(new_path);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_path);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: Handle this case */
		chdir((new_path = _getenv(info, "OLDPWD=")) ? new_path : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Failed to change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * show_help - Display help information.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int show_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help command is functioning. Functionality not yet implemented.\n");
	if (0)
		_puts(*arg_array); /* Temporary unused workaround */
	return (0);
}
