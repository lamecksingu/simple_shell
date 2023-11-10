#include "shell.h"
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 always success
 */
int main(int argc, char *argv[])
{
	char *command;
	int err;

	if (argc == 0)
	{
		write(1, "Error", 5);
	}
	while (1)
	{
		prompt();
		command = user_input();
		if (!command)
		{
			break;
		}
		/*remove the newline character*/
		if (command[strlen(command) - 1] == '\n')
		{
			command[strlen(command) - 1] = '\0';
		}
		err = execute_command(command);
		free(command);
		if (err == -1)
		{
			dprintf(STDERR_FILENO, "%s: No such file or directory\n", argv[0]);
			return (-1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
