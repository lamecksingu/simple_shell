#include "shell.h"
/**
 * free_tokens - free the memory allocated for tokens array
 * @tokens: The token arrays
 * @count: the number of tokens
 */
void free_tokens(char **tokens, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}
