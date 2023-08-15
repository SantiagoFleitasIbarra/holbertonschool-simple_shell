#include "shell.h"
/***/
void execute_command(char **tokens)
{
	if (tokens[0][0] == '/' || tokens[0][0] == '.')
	{
		direct_execute(tokens);
		return;
	}
	path_execute(tokens);
}
/***/
void direct_execute(char **tokens)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(tokens[0], tokens, environ) == -1)
		{
			fprintf(stderr, "%s: %s\n", tokens[0], strerror(errno));
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0)
		perror("./shell");
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
/***/
void path_execute(char **tokens)
{
	pid_t pid;
	int status;
	path_t *path_list;
	char *full_path;

	path_list = parse_path();
	full_path = search_path(tokens[0], path_list);
	if (full_path)
	{
		free(tokens[0]);
		tokens[0] = full_path;
		pid = fork();
		if (pid == 0)
		{
			if (execve(tokens[0], tokens, environ) == -1)
			{
				fprintf(stderr, "%s: %s\n", tokens[0], strerror(errno));
				exit(EXIT_FAILURE);
			}
		} else if (pid < 0)
			perror("./shell");
		else
		{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	else
		fprintf(stderr, "%s: command not found\n", tokens[0]);
	free_path_list(path_list);
}
