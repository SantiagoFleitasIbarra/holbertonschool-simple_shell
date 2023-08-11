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
		/** Proceso hijo */
		if (execlp(command, command, NULL) == -1)
		{
			perror("execlp");
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
