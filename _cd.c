#include "shell.h"
/**
 * _cd - implement the dc command
 * @directory: path to where the dir is changed
 */
void _cd(const char *directory)
{
	char *new_directory;
	char current_directory[1024];

	if (directory == NULL || _strlen(directory) == 0)/*same as $HOME*/
	{
		new_directory = getenv("HOME");
		if (new_directory == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return;
		}
	} else if (strcmp(directory, "-") == 0)
	{
		new_directory = getenv("OLDPWD");/*handle '-'*/
		if (new_directory == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return;
		}
		printf("%s\n", new_directory);
	} else
	{
		new_directory = (char *)directory;
	}
	/*get the current working directory before changing*/
	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		perror("getwcd");
		return;
	}
	if (chdir(new_directory) != 0)/*change directory*/
	{
		perror("chdir");
		return;
	}
	if (setenv("OLDPWD", current_directory, 1) != 0)/*update PWD &OLDPWD*/
	{
		perror("setenv");
		return;
	}
}

/**
 * h_cd_command - handles the custom cd command in main
 * @command: user input command
 */
void h_cd_command(const char *command)
{
	/*Assuming the format is "cd [DIRECTORY]"*/
	const char *args = command + _strlen("cd");
	char *directory;/* = _strtok(args, " ");*/
	char *args_copy = strdup(args);/*create a non constant copy*/

	if (args_copy == NULL)
	{
		perror("Strdup");
		return;
	}

	directory = _strtok(args_copy, " ");
	if (directory == NULL)
	{
		directory = getenv("HOME");
	}
	_cd(directory);
	free(args_copy);
}
