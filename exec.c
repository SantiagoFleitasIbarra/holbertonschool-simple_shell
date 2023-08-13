# include "shell.h"
/**
 * execute_command - manages the execution of external commands in the shell
 * @args: string arrangement
*/
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("Error");
		exit(EXIT_FAILURE);
	} else if (pid > 0)
		wait(NULL);
	else
		perror("Fork failed");
}
/**
 * execute_input - executes a command provided as an argument
 * @args: string arrangement
*/
void execute_input(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		exit(0);
	else if (strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	} else if (strcmp(args[0], "cd") == 0)
	{
		handle_cd(args);
	} else if (strcmp(args[0], "help") == 0)
	{
		handle_help();
	} else if (strcmp(args[0], "setenv") == 0)
	{
		handle_setenv(args);
	} else if (strcmp(args[0], "unsetenv") == 0)
	{
		handle_unsetenv(args);
	}
	else
	{
		if (is_absolute_path(args[0]))
		{
			if (access(args[0], X_OK) == 0)
				execute_command(args);
			else
			{
				perror(args[0]);
				exit(EXIT_FAILURE);
			}
		} else
		{
			search_and_execute(args);
		}

	}
}
/**
 * search_and_execute - search for a command in the PATH locations
 * @args: an arrangement of strings
*/
void search_and_execute(char **args)
{
	char *path = getenv("PATH");

	if (args[0] == NULL)
		return;

	if (path)
	{
		char path_copy[MAX_INPUT_SIZE];
		char *dir = strtok(path_copy, ":");

		strcpy(path_copy, path);
		while (dir)
		{
			char command_path[MAX_INPUT_SIZE];

			snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);
			if (access(command_path, X_OK) == 0)
			{
				args[0] = command_path;
				execute_command(args);
				return;
			}
			dir = strtok(NULL, ":");
		}
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
}
