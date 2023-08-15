#include "shell.h"
/**
 * parse_input - Tokenises the input line
 * @input: The input line
 * Return: Array of tokens
 */
char **parse_input(char *input)
{
	char **tokens;
	size_t bufsize = BUFFER_SIZE, position = 0;
	char *token;

	input[strcspn(input, "\n\r")] = '\0';
	token = strtok(input, " \t\n\"");
	if (!token)
	{
		return (init_token());
	}

	tokens = malloc(bufsize * sizeof(char *));
	check_allocation(tokens);

	while (token)
	{
		tokens[position++] = strdup(token);
		if (position >= bufsize)
			tokens = resize_token_buffer(tokens, &bufsize);
		token = strtok(NULL, " \t\n\"");
	}
	tokens[position] = NULL;
	return (tokens);
}
/**
 * init_token - Initialize a token
 * Return: Initialized token
 */
char **init_token(void)
{
	char **tokens;

	tokens = malloc(sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	tokens[0] = NULL;
	return (tokens);
}
/**
 * check_allocation - Checks memory allocation
 * @tokens: The allocated memory
 */
void check_allocation(char **tokens)
{
	if (!tokens)
	{
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}
}
/**
 * resize_token_buffer - Resizes the token buffer
 * @tokens: The token buffer
 * @bufsize: The buffer size
 * Return: The resized buffer
 */
char **resize_token_buffer(char **tokens, size_t *bufsize)
{
	*bufsize += BUFFER_SIZE;
	tokens = realloc(tokens, *bufsize * sizeof(char *));
	check_allocation(tokens);
	return (tokens);
}
