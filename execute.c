#include "shell.h"
/**
 * execute_command - a function to execute commands
 * @command: a command to be executed
 * Return: -1 on error, 0 on success
 */
int execute_command(const char *command)
{
	pid_t child_pid;
	char *command_copy;
	char *args[2];
	int status;
	int err;

	if (command == NULL)
	{
		write(STDERR_FILENO, "Invalid command\n", 24);
		return (-1);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error in fork");
		exit(1);
	}
	if (child_pid == 0)
	{
		command_copy = strdup(command);
		if (command_copy == NULL)
		{
			perror("Error duplicating command");
			exit(1);
		}
		args[0] = command_copy;
		args[1] = NULL;/*NULL terminate the array*/
		err = execve(command_copy, args, environ);
		if (err == -1)
		{
			return (-1);
		}
		free(command_copy);
		exit(127);
	} else
	{
		waitpid(child_pid, &status, 0);
	}
	return (0);
}
