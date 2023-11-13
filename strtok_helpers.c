#include "shell.h"
/**
 * _strlen -  a function to compute the length of a string
 * @str: input string
 * Return: length of the string
 */
size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * _strcpy - a function to copy a string
 * @dest: destination buffer
 * @src: source string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	char *start = dest;

	while ((*dest++ = *src++) != '\0')
		;
	return (start);
}

/**
 * _strcspn - compute the length of the initial part of a string consisting
 * of characters not in another string
 * @str: input string
 * @reject: string containing characters to avoid
 * Return: length of the initial part of str
 */
size_t _strcspn(const char *str, const char *reject)
{
	size_t len = 0;

	while (*str && !_strchr(reject, *str++))
	{
		len++;
	}
	return (len);
}

/**
 * _strchr - locate the first occurance of a character in a string
 * @str: input string
 * @c: character to find
 * Return: pointer to the first occurance of c in str
 * or NULL if not found
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

/**
 * _strspn - compute the length of the initial part of a string
 * consisting of characters from another string
 * @str: input string
 * @accept: string containing characters to match
 * Return: length of the initial part of str
 */
size_t _strspn(const char *str, const char *accept)
{
	size_t len = 0;

	while (*str && _strchr(accept, *str++))
	{
		len++;
	}
	return (len);
}
