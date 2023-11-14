#include "shell.h"
/**
 * exit_shell - Exit the shell
 * @command: the command string containing the exit status
 */
void exit_shell(const char *command)
{
	int status = 0;

	if (strncmp(command, "exit", _strlen("exit")) == 0)
	{
		/*assuming the format is "exit status"*/
		status = atoi(command + _strlen("exit"));
		exit(status);
	} else if (strcmp(command, "exit") == 0)
	{
		/*free(command);*/
		exit(0);
	}
}
