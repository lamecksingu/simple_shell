#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
extern char **environ;

void prompt(void);
char *user_input(void);
int execute_command(const char *command, const char *path);
char **tokenize(const char *str, const char *delim, int *count);
void free_tokens(char **tokens, int count);
char *find_command_path(const char *command, const char *path);
int execute_child_process(const char *full_path, char **args);
int check_command(const char *command, const char *path);
void exit_shell(const char *command);
void env_builtin(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void expand_buffer(char **lineptr, size_t *n, size_t required_size);
ssize_t read_into_buffer(FILE *stream);
size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
size_t _strcspn(const char *str, const char *reject);
char *_strchr(const char *str, int c);
size_t _strspn(const char *str, const char *accept);
char *_strtok(char *str, const char *delim);
int _setenv(const char *variable, const char *value);
int _unsetenv(const char *variable);
int h_setenv_command(const char *command);
int h_unsetenv_command(const char *command);

#endif
