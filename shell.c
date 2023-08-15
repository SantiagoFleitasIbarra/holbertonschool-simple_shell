# include "shell.h"
/***/
int main(void)
{
	char *input_line = NULL;
	size_t len = 0;
	ssize_t read;
	char **tokens;

	while (1)
	{
		printf("#cisfun$ ");
		read = getline(&input_line, &len, stdin);

		if (read == -1)
		{
			free(input_line);
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		tokens = parse_input(input_line);

		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}

		if (strcmp(tokens[0], "exit") == 0)
		{
			free(tokens);
			free(input_line);
			exit(EXIT_SUCCESS);
		}
		execute_command(tokens);
		free(tokens);
	}
	free(input_line);
	return (EXIT_SUCCESS);
}
