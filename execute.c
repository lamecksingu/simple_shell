#include "shell.h"
/**
 * execute_command - a function to execute commands
 * @command: a command to be executed
 * Return: -1 on error, 0 on success
 */
int execute_command(const char *command)
{
	pid_t child_pid;/*char *command_copy;*/
	char **args;
	int status, err, arg_count;

	if (command == NULL)
	{
		write(STDERR_FILENO, "Invalid command\n", 24);
		return (-1);
	}
	/*tokenize the command string*/
	args = tokenize(command, " ", &arg_count);
	if (args == NULL)
	{
		perror("Error tokenizing command string");
		exit(EXIT_FAILURE);
	}
	/*fork a child process*/
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error in fork");
		free_tokens(args, arg_count);/*free allocated memory*/
		exit(1);
	}
	if (child_pid == 0)
	{
		err = execve(args[0], args, environ);
		if (err == -1)
		{
			free_tokens(args, arg_count);/*free allocated memory*/
			return (-1);
		}
	} else
	{
		waitpid(child_pid, &status, 0);
		free_tokens(args, arg_count);/*free allocated memory*/
	}
	return (0);
}
