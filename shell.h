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
int execute_command(const char *command);

#endif
