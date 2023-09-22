#include "shell.h"
/**
 * _strtoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer or -1 on error.
 */
int _strtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printErrorMessage - Prints an error message.
 * @info: The parameter and return info struct.
 * @errorMessage: String containing the specified error type.
 */
void printErrorMessage(info_t *info, char *errorMessage)
{
	_eputs(info->fname);
	_eputs(": ");
	printInteger(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(errorMessage);
}

/**
 * printInteger - Prints an integer.
 * @input: The integer to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int printInteger(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertToBase - Converts a number to a given base.
 * @num: The number to convert.
 * @base: The base to convert to.
 * @flags: Argument flags.
 *
 * Return: The converted string.
 */
char *convertToBase(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do

	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * stripComments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 */
void stripComments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
