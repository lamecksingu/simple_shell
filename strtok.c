#include "shell.h"
/**
 * _strtok - tokenize the string based on delimiter
 * @str: string to be tokenized
 * @delim: the delimeter for tokenization
 * Return: A pointer to the next token or NULL if no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *current;
	char *start;

	if (str != NULL)
	{
		current = str;
	} else if (current == NULL || *current == '\0')
	{
		return (NULL);/*No more tokens*/
	}
	/*skip leading delimiters*/
	while (*current != '\0' && _strchr(delim, *current) != NULL)
	{
		++current;
	}
	if (*current == '\0')
	{
		current = NULL;
		return (NULL);/*No more tokens*/
	}
	start = current;
	/*find the end of the token*/
	while (*current != '\0' && _strchr(delim, *current) == NULL)
	{
		++current;
	}
	if (*current != '\0')
	{
		*current = '\0';
		++current;/*move to the next character for the next call*/
	} else
	{
		current = NULL;
	}
	return (start);
}
