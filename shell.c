# include "shell.h"
/**
 * main - main program entry
 * Return: 0 Always (Success)
*/
int main(void)
{
	char input[MAX_INPUT_SIZE], *tokens[MAX_TOKENS];

	while (1)
	{
		int token_count = 0, i;
		struct InternalCommand *internal_cmds = get_internal_commands();

		display_prompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
				perror("fgets"), exit(EXIT_FAILURE);
		}
		input[strcspn(input, "\n")] = '\0';
		if (input[0] == '\0')
			break;
		token_count = tokenize_input(input, tokens, MAX_TOKENS);
		for (i = 0; internal_cmds[i].name != NULL; i++)
		{
			if (strcmp(tokens[0], internal_cmds[i].name) == 0)
			{
				internal_cmds[i].function(tokens);
				break;
			}

		}
		if (internal_cmds[i].name == NULL)
			execute_command(tokens);
		for (i = 0; i < token_count; i++)
			free(tokens[i]);
	}
	return (0);
}
/**
 * display_prompt - displays the prompt indicator in the shell interface
*/
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/**
 * tokenize_input - splitting the input string into tokens
 * @input: a pointer to a string containing the user's input
 * @tokens: this is an array of pointers to characters
 * @max_tokens: this parameter indicates the maximum length of the token array
 * Return: total number of tokens found
*/
int tokenize_input(char *input, char *tokens[], int max_tokens)
{
	int token_count = 0;
	char *token = strtok(input, " \t\n");

	while (token != NULL && token_count < max_tokens)
	{
		tokens[token_count++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	tokens[token_count] = NULL;
	return (token_count);
}
