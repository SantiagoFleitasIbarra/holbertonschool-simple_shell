#include "shell.h"

extern char **environ;

/***/
char *_getenv(const char *name)
{
	size_t name_len = strlen(name);
	size_t i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], name_len) == 0 && environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
	}
	return (NULL);
}
/***/
void print_error(const char *command, const char *message)
{
	fprintf(stderr, "%s: %s\n", command, message);
}
