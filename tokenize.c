#include "shell.h"
/**
 * tokenize - tokenize the string based on delimiter
 * @str: the string to be tokenized
 * @delim: the delimiter for tokenization
 * @count: A pointer to store the number of tokens
 * Return: An array of tokens
 */
char **tokenize(const char *str, const char *delim, int *count)
{
	char *token;
	int i, token_count = 0;
	char *copy;
	char **tokens;

	/*count the num er of tokens*/
	copy = strdup(str);
	if (copy == NULL)
	{
		return (NULL);
	}
	token = strtok(copy, delim);
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, delim);
	}
	free(copy);

	/*allocate memory for tokens array*/
	tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		return (NULL);
	}

	/*copy tokens to the array*/
	token = strtok((char *)str, delim);
	for (i = 0; i < token_count; i++)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, delim);
	}
	tokens[token_count] = NULL;
	*count = token_count;
	return (tokens);
}
