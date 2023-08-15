#include "shell.h"

extern char **environ;

/***/
void main_loop(void)
{
	char *line;
	size_t len = 0;
	ssize_t nread;
	PathNode *path_list = NULL;
	char *path_env = _getenv("PATH");
	int execution_status = 0;

	signal(SIGINT, SIG_IGN);

	if (path_env != NULL)
		parse_path(path_env, &path_list);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}
		line[nread - 1] = '\0';
		if (strcmp(line, "exit") == 0)
		{
			free_path_list(path_list);
			free(line);
			exit(EXIT_SUCCESS);
		} else if (strcmp(line, "env") == 0)
		{
			char **env = environ;

			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
		}
		else
		{
			execute_command(line, path_list);
			if (execution_status == EXECUTION_ERROR)
				print_error(line, NULL);
		}
	}
	free_path_list(path_list);
	free(line);
}
