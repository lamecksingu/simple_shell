#include "shell.h"
/**
 * user_input - a function to accepts user input
 * Return: the string read from input
 */
char *user_input(void)
{
	char *input = NULL;
	size_t bufsize = 0;
	ssize_t bytes_read = getline(&input, &bufsize, stdin);

	if (bytes_read == -1)
	{
		free(input);
		input = NULL;
	}
	return (input);
}
