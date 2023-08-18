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
		fprintf(stderr, "%s: %s\n", args[0], strerror(errno));
		/*perror(args[0]);*/
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		int status;

		do
			waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
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
	{
		free(args[0]);
		handle_exit(args);
		return;
	}
	if (strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	} else if (strcmp(args[0], "cd") == 0)
		handle_cd(args);
	else if (strcmp(args[0], "help") == 0)
		handle_help();
	else if (strcmp(args[0], "setenv") == 0)
		handle_setenv(args);
	else if (strcmp(args[0], "unsetenv") == 0)
		handle_unsetenv(args);
	else
	{
		if (is_absolute_path(args[0]))
		{
			if (access(args[0], X_OK) == 0)
				execute_command(args);
			else
				fprintf(stderr, "%s: %s\n", args[0], strerror(errno));
		} else
			search_and_execute(args);
	}
}
/**
 * search_and_execute - search for a command in the PATH locations
 * @args: an arrangement of strings
*/
void search_and_execute(char **args)
{
	char *path = _getenv("PATH");

	if (args[0] == NULL)
		return;

	if (path)
	{
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");

		strcpy(path_copy, path);
		while (dir)
		{
			char command_path[MAX_INPUT_SIZE];

			snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);
			if (access(command_path, X_OK) == 0)
			{
				args[0] = strdup(command_path);
				execute_command(args);
				free(args[0]);
				free(path_copy);
				return;
			}
			dir = strtok(NULL, ":");
		}
		fprintf(stderr, "%s: command not found\n", args[0]);
		free(path_copy);
	}

}
/**
 * _getenv - retrieves the value of an environment variable
 * @name: name of the environment variable to retrieve
 *
 * Return: pointer to the value of the environment variable,
 * or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
		i++;
	}
	return (NULL);
}
/**
 * _atoi - converts a string into an integer
 * @str: pointer to a string
 * Return: the integer
*/
int _atoi(const char *str)
{
	int i, integer, sign = 1;

	i = 0;
	integer = 0;
	while (!((str[i] >= '0') && (str[i] <= '9')) && (str[i] != '\0'))
	{
		if (str[i] == '-')
		{
			sign = sign * (-1);
		}
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		integer = (integer * 10) + (sign * (str[i] - '0'));
		i++;
	}
	return (integer);
}
