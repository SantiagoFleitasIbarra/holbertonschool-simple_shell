#include "shell.h"
/**
 * execute_command - function to execute a command
 * @command: command
*/
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		dup2(STDOUT_FILENO, STDERR_FILENO);

		/** Proceso hijo */
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/** Proceso padre */
		int status;

		waitpid(pid, &status, 0);
	}
}
/**
 * parse_command - function for splitting the command line into arguments
 * @input: input
 * @args: argument string
 * @argc: argument counts
*/
void parse_command(char *input, char **args, int *argc)
{
	char *token = strtok(input, " \t\n");
	*argc = 0;

	while (token != NULL && *argc < MAX_ARGS)
	{
		args[(*argc)++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[*argc] = NULL;
}
