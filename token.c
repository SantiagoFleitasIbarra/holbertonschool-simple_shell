#include "shell.h"
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

static char *token_buffer;
static size_t token_buffer_size;

/***/
void init_token(void)
{
	token_buffer_size = TOKEN_BUFFER_SIZE;
	token_buffer = (char *)malloc(token_buffer_size * sizeof(char));
	check_allocation(token_buffer);
}
/***/
void check_allocation(void *ptr)
{
	if (!ptr)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
}
/***/
void resize_token_buffer(void)
{
	token_buffer_size += TOKEN_BUFFER_SIZE;
	token_buffer = (char *)realloc(token_buffer, token_buffer_size *
			sizeof(char));
	check_allocation(token_buffer);
}
/***/
char *parse_input(void)
{
	char *line = NULL;
	size_t line_buffer_size = 0;
	ssize_t line_size = getline(&line, &line_buffer_size, stdin);

	if (line_size == -1)
	{
		perror("getline error");
		exit(EXIT_FAILURE);
	}
	line[line_size - 1] = '\0';
	return (line);
}
/***/
char **tokenize(char *line)
{
	int token_buffer_size = TOKEN_BUFFER_SIZE;
	int position = 0;
	char **tokens = malloc(token_buffer_size * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOKEN_DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= token_buffer_size)
		{
			token_buffer_size += TOKEN_BUFFER_SIZE;
			tokens = realloc(tokens, token_buffer_size * sizeof(char *));
			if (!tokens)
			{
				perror("Reallocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[position] = NULL;
	return (tokens);
}
