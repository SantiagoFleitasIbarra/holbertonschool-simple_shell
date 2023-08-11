#include "shell.h"
/**
 * display_prompt - function to display the prompt
*/
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/**
 * main - main function
 * Return: Always 0 (Success)
*/
int main(void)
{
	char command[MAX_COMMAND_LENGTH + 1];

	while (1)
	{
		display_prompt();

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("fgets");
				exit(EXIT_FAILURE);
			}
		}
		command[strcspn(command, "\n")] = '\0';

		if (strlen(command) > 0)
			execute_command(command);
	}
	return (0);
}
