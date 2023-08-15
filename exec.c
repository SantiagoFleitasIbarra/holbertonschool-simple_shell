#include "shell.h"

extern char **environ;

/***/
void direct_execute(char *cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		char *args[2];

		args[0] = cmd;
		args[1] = NULL;
		if (execve(cmd, args, NULL) == -1)
		{
			perror(cmd);
			_exit(EXIT_FAILURE);
		}
	} else if (child_pid < 0)
		perror("Fork error");
	else
		wait(&status);
}
/***/
void path_execute(char *cmd, char **args, PathNode *path_list)
{
	char *full_path = search_path(cmd, path_list);

	if (full_path != NULL)
	{
		direct_execute_args(full_path, args);
		free(full_path);
	} else
		print_error(cmd, "command not found");
}
/***/
void execute_command(char *cmd, PathNode *path_list)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		direct_execute(cmd);
	else
	{
		char **args = tokenize(cmd);

		if (args[0])
			path_execute(args[0], args, path_list);
		free(args);
	}
}
/***/
void direct_execute_args(char *cmd, char **args)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			execve(cmd, args, environ);
		}
		else
			print_error(cmd, strerror(errno));
	} else if (child_pid < 0)
		print_error("fork", strerror(errno));
	else
		wait(&status);
}
