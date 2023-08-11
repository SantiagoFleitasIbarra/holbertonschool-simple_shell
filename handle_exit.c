#include "shell.h"

/**
 * handle_exit - implement the built-in exit command
 * @args: string arrangement
 */
void handle_exit(char **args)
{
	(void)args;
	exit(0);
}
