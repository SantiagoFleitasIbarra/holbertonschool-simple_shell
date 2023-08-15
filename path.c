#include "shell.h"

extern char **environ;

/***/
void parse_path(const char *path, PathNode **path_list)
{
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	*path_list = NULL;

	if (path == NULL)
		return;
	
	if (!path_copy)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	while (token != NULL)
	{
		PathNode *new_node = (PathNode *)malloc(sizeof(PathNode));
		if (!new_node)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		new_node->dir = strdup(token);
		new_node->next = *path_list;
		*path_list = new_node;
		token = strtok(NULL, ":");
	}
	free(path_copy);
}
/***/
char *search_path(const char *cmd, PathNode *path_list)
{
	while (path_list != NULL)
	{
		char *full_path = (char *)malloc(strlen(path_list->dir) + strlen(cmd) + 2);
		if (!full_path)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		strcpy(full_path, path_list->dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		path_list = path_list->next;
	}
	return (NULL);
}
/***/
void free_path_list(PathNode *path_list)
{
	while (path_list != NULL)
	{
		PathNode *temp = path_list;
		path_list = path_list->next;
		free(temp->dir);
		free(temp);
	}
}
