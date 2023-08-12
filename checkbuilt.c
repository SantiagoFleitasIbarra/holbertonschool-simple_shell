# include "shell.h"
/**
 * get_internal_commands - function for internal commands
 * Return: internal command
*/
struct InternalCommand *get_internal_commands()
{
	static struct InternalCommand internal_commands[] = {
		{"cd", cd_command},
		{"exit", exit_command},
		{"env", env_command},
		{NULL, NULL}
	};
	return (internal_commands);
}
