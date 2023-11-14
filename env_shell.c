#include "shell.h"
/**
 * env_builtin - print the current environment
 */
void env_builtin(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * _setenv - set or modify an environment variable
 * @variable: Name of the environment variable
 * @value: Value to set for the environment variable
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *variable, const char *value)
{
	size_t size;
	char *new_env_var;

	if (variable == NULL || value == NULL)
	{
		dprintf(STDERR_FILENO, "Usage: _setenv VARIABLE VALUE\n");
		return (-1);
	}
	/*check if the variable already exists*/
	if (getenv(variable) != NULL)
	{
		dprintf(STDERR_FILENO, "Variable %s already exist", variable);
		return (-1);
	}
	/*construct the new environment variable*/
	size = _strlen(variable) + _strlen(value) + 2;
	new_env_var = malloc(size);
	if (new_env_var == NULL)
	{
		perror("Malloc failed");
		return (-1);
	}
	snprintf(new_env_var, size, "%s=%s", variable, value);
	/*add the new environment variable*/
	if (putenv(new_env_var) != 0)
	{
		perror("putenv failed");
		free(new_env_var);
		return (-1);
	}
	return (0);
}

/**
 * _unsetenv - unset an environment variable
 * @variable: Name of the environment variable to unset
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *variable)
{
	size_t size;
	char *env_var;

	if (variable == NULL)
	{
		dprintf(STDERR_FILENO, "Usage: _unsetenv VARIABLE\n");
		return (-1);
	}
	/*check if the variable exists*/
	if (getenv(variable) == NULL)
	{
		dprintf(STDERR_FILENO, "variable %s doesn't exist\n", variable);
		return (-1);
	}
	/*construct the environment variable to be removed*/
	size = _strlen(variable) + 2;
	env_var = malloc(size);
	if (env_var == NULL)
	{
		perror("Malloc failed");
		return (-1);
	}
	snprintf(env_var, size, "%s=", variable);
	/*remove the environment variable*/
	if (putenv(env_var) != 0)
	{
		perror("Putenv failed");
		free(env_var);
		return (-1);
	}
	return (0);
}

/**
 * h_setenv_command - handles setenv builtin command
 * @command: user entered command
 * Return: 0 on success, -1 on failure
 */
int h_setenv_command(const char *command)
{
	const char *args, *variable, *value;
	char *args_copy;

	/*assuming the format is setenv VARIABLE VALUE*/
	if (strncmp(command, "setenv", _strlen("setenv")) == 0)
	{
		args = command + _strlen("setenv");
		args_copy = strdup(args);
		if (args_copy == NULL)
		{
			perror("Error duplicating string");
			return (-1);
		}
		variable = _strtok(args_copy, " ");
		value = _strtok(NULL, " ");
		if (variable != NULL && value != NULL)
		{
			if (_setenv(variable, value) == -1)
			{
				dprintf(STDERR_FILENO, "Failed to set environment varaible\n");
				return (-1);
			}
			/*return (0);*/
		} else
		{
			dprintf(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n");
			return (-1);
		}
	}
	free(args_copy);
	return (-1);/*Indicate failure for unsupported commands*/
}

/**
 * h_unsetenv_command - handles unsetenv builtin command
 * @command: user entered command
 * Return: 0 on success, -1 on failure
 */
int h_unsetenv_command(const char *command)
{
	char *variable = NULL;

	/*assuming the format is "unset VARIABLE*/
	if (strncmp(command, "unsetenv", _strlen("unsetenv")) == 0)
	{
		if (_unsetenv(variable) == -1)
		{
			/*print an error if _unsetenv fails*/
			dprintf(STDERR_FILENO, "Failed to unset environment variable\n");
			return (-1);
		}
		return (0);
	}
	return (-1);/*indicates failure for unsupported commands*/
}
