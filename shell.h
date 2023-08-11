#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define MAX_ARGS 10
#define MAX_COMMAND_LENGTH 40
void execute_command(char *command);
void display_prompt(void);
int main(void);
void parse_command(char *input, char **args, int *argc);
#endif
