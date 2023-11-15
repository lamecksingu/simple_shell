#include "shell.h"
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 always success
 */
int main(int argc, char *argv[])
{
	char *command;/* *args, *directory;*/
	const char *path = "/bin/";
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
		if (command[_strlen(command) - 1] == '\n')
		{
			command[_strlen(command) - 1] = '\0';
		}
		if (strcmp(command, "env") == 0)
		{
			env_builtin();
		} else if (strncmp(command, "cd", _strlen("cd")) == 0)
		{
			h_cd_command(command);
		} else
		{
			exit_shell(command);
			err = execute_command(command, path, argv[0]);
			if (err == -1)
			{
				dprintf(STDERR_FILENO, "%s: No such file or directory\n", argv[0]);
				return (-1);
			}
		}
		free(command);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
