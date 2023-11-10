#include "shell.h"
/**
 * prompt - prompts for input from stdin
 */
void prompt(void)
{
	char *word = "#cisfun$ ";
	int err;

	err = write(1, word, 9);
	if (err  == -1)
	{
		perror("Write failed");
	}
}
