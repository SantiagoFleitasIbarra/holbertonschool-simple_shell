# include "shell.h"
/**
 * cd_command - function of the cd command
 * @args: argument string
*/
void cd_command(char **args)
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
	else
	{
		fprintf(stderr, "cd: missing argument\n");
	}
}
/**
 * exit_command - function of the exit command
 * @args: argument string
*/
void exit_command(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	exit(0);
}
/**
 * env_command - function of the env command
 * @args: argument string
*/
void env_command(char **args)
{
	char **env = environ;

	(void)args;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
