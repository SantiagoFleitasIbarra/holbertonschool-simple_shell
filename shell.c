# include "shell.h"
/**
 * main - main program entry
 * Return: 0 Always (Success)
*/
int main(void)
{
	if (!isatty(STDIN_FILENO))
		handle_noninteractive_mode(stdin);
	else
	{
		while (1)
		{
			char *line = NULL;
			char *args[MAX_INPUT_SIZE / 2 + 1];
			size_t len = 0;

			display_prompt();
			if (getline(&line, &len, stdin) == -1)
			{
				free(line);
				printf("\n");
				exit(EXIT_SUCCESS);
			}
			line[strcspn(line, "\n")] = '\0';
			tokenize_input(line, args);
			if (args[0] != NULL)
				execute_input(args);
		}
	}
	return (0);
}
/**
 * tokenize_input - splits an input string into tokens
 * @input: input string
 * @args: string arrangement
*/
void tokenize_input(char *line, char **args)
{
	char *token = strtok(line, " \t");
	int i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;
}
/**
 * handle_noninteractive_mode - handles command execution in non-interactive
 * mode
*/
void handle_noninteractive_mode(FILE *input)
{
	char *line = NULL;
	size_t len = 0;

	while (getline(&line, &len, input) != -1)
	{
		char *args[MAX_INPUT_SIZE / 2 + 1];

		line[strcspn(line, "\n")] = '\0';
		tokenize_input(line, args);

		if (args[0] != NULL)
		{
			execute_input(args);
			if (isatty(STDIN_FILENO))
				display_prompt();
		}
	}
	free(line);
}
/**
 * is_absolute_path - checks whether a command is an absolute path or not
 * @command: command to be executed
 * Return: an integer value
 * 1, means that the command is an absolute path. If it returns
 * 0, the command is not an absolute path
*/
int is_absolute_path(char *command)
{
	return (strchr(command, '/') != NULL);
}
