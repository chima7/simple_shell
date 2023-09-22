#include "shell.h"

/**
 * _custom_strncpy - Copies a string with a specified length.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 * Return: A pointer to the concatenated string.
 */
char *_custom_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * _custom_strncat - Concatenates two strings with a specified length.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to use.
 * Return: A pointer to the concatenated string.
 */
char *_custom_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';

	return (result);
}

/**
 * _custom_strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to find.
 * Return: A pointer to the first occurrence of the character in the string.
 */
char *_custom_strchr(char *s, char c)
{
	do

	{
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
