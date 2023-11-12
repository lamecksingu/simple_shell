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
void exit_shell(void);

#endif
