#include "shell.h"
/**
 * execute_command - a function to execute commands
 * @command: a command to be executed
 * @path: the path to the command
 * @program_name: name of the programe eg ./hsh
 * Return: -1 on error, 0 on success
 */
int execute_command(const char *command, const char *path,
		const char *program_name)
{
	pid_t child_pid;/*char *command_copy;*/
	char **args;
	int status, arg_count;
	char *full_path;

	/*check if command is NULL or the path*/
	check_command(command, path);
	args = tokenize(command, " ", &arg_count);/*tokenize the command string*/
	if (args == NULL)
	{
		perror("Error tokenizing command string");
		return (-1);
	}
	full_path = find_command_path(args[0], path);/*find the full path*/
	if (full_path != NULL && access(full_path, F_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error in fork");
			free_tokens(args, arg_count);/*free allocated memory*/
			return (-1);
		}
		if (child_pid == 0)
		{
			execute_child_process(full_path, args);
			free_tokens(args, arg_count);/*free allocated memory*/
		} else
		{
			waitpid(child_pid, &status, 0);
			free_tokens(args, arg_count);/*free allocated memory*/
		}
		free(full_path);
	} else
	{
		dprintf(STDERR_FILENO, "%s: No such file or directory\n", program_name);
		free_tokens(args, arg_count);
		return (0);
	}
	return (0);
}

/**
 * find_command_path - find the full path of a command in the PATH
 * @command: the command to find
 * @path: the PATH environment variable
 * Return: The full path of the command or NULL if not found
 */
char *find_command_path(const char *command, const char *path)
{
	char *token, *copy, *full_path;

	if (command == NULL || path == NULL)
	{
		return (NULL);
	}
	/*check if the command is an absolute path or relative path*/
	if (access(command, F_OK) == 0)
	{
		return (strdup(command));
	}
	copy = strdup(path);
	if (copy != NULL)
	{
		token = strtok(copy, ":");
		while (token != NULL)
		{
			/*construct a full path to the command*/
			full_path = (char *)malloc(strlen(token) + strlen(command) + 2);
			if (full_path != NULL)
			{
				strcpy(full_path, token);
				strcat(full_path, "/");
				strcat(full_path, command);
				/*check if the constructed path exist*/
				if (access(full_path, F_OK) == 0)
				{
					break;
				}
				free(full_path);
			}
			token = strtok(NULL, ":");
		}
		free(copy);
	}
	return (full_path);
}

/**
 * execute_child_process - a function to execute child process
 * @full_path: the path to the executable
 * @args: arguments
 * Return: -1 on failure. On success 0 to the child
 * and pid of the chile to the parent
 */
int execute_child_process(const char *full_path, char **args)
{
	if (execve(full_path, args, environ) == -1)
	{
		return (-1);
	}
	return (0);
}

/**
 * check_command - a function to check if the command is NULL or not
 * @command: the command provided
 * @path: path to the executable
 * Return: -1 if command is NULL and 0 if command is not NULL
 */
int check_command(const char *command, const char *path)
{
	if (command == NULL || path == NULL)
	{
		write(STDERR_FILENO, "Invalid command\n", 24);
		return (-1);
	}
	return (0);
}
