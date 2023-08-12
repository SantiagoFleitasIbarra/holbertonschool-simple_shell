#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100

/**
 * struct InternalCommand - structure for internal commands
 * @name: stores the name of the internal command
 * @function: is a pointer to a function
*/
typedef struct InternalCommand
{
	char *name;
	void (*function)(char **args);
} InternalCommand;

struct InternalCommand *get_internal_commands();

extern char **environ;

void cd_command(char **args);
void exit_command(char **args);
void env_command(char **args);
void execute_external_command(char **args);
char *search_path(char *command);
char *get_absolute_path(char *command);
void execute_command(char **args);
int main(void);
void display_prompt(void);
int tokenize_input(char *input, char *tokens[], int max_tokens);

#endif
