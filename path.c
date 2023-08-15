#include "shell.h"
/**
 * _getenv - retrieves the value of an environment variable
 * @name: name of the environment variable to retrieve
 * 
 * Return: pointer to the value of the environment variable,
 * or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len = strlen(name);
	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return &environ[i][len + 1];
		}
		i++;
	}
	return (NULL);
}
/**
 * parse_path - Builds a linked list of directories from PATH
 * Return: Pointer to the head of the linked list
 *
 * This function tokenises the PATH variable using : (delimiter) 
 * and stores each directory into a node in a sing linked list.
 */
path_t *parse_path(void)
{   /* Retrieving the PATH environment variable */
	char *ori_path;
	char *path; /* cp PATH before tokenising */
	char *token;
	path_t *head = NULL, *new_node, *temp;

	if ((ori_path = _getenv("PATH")) == NULL)
		return (NULL);

	path = strdup(ori_path);

	if (!path)
		exit(EXIT_FAILURE);

	token = strtok(path, ":"); /* Start tokenising PATH variable */
	while (token) /* Iterate through each tokenised directory */
	{
		new_node = malloc(sizeof(path_t));/* For new directory node */
		if (!new_node)
			exit(EXIT_FAILURE);
        /* Copying the tokenised directory to the new node */
		new_node->dir = strdup(token);
		new_node->next = NULL;
		if (!head) /* If it's the first directory, set it as head */
			head = new_node;
		else
		{   /* Otherwise append to the end of the linked list */
			temp = head;
			while (temp->next)
				temp = temp->next;
			temp->next = new_node;
		}
		token = strtok(NULL, ":"); /*Continue tokenising nxt dirtry*/
	}
	free(path); /* Free the copied PATH */
	return (head);
}
/**
 * search_path - Searches for an executable in PATH directories
 * @cmd: The command to find
 * @path_list: The linked list of PATH directories
 * Return: Full path to executable or NULL if not found
 *
 * This fn iterates through the linked list of directories,
 * adding the provided cmd and checking if the returned full
 * path is valid and executable.
 */
char *search_path(char *cmd, path_t *path_list)
{
	char *full_path;
	struct stat st;

	while (path_list) /* Iterate through each dirtry in linked list */
	{ /* Allocate memory for the full path of the command */
		full_path = malloc(strlen(path_list->dir) + strlen(cmd) + 2);
		if (!full_path)
			exit(EXIT_FAILURE);
        /* Build the full path */
		strcpy(full_path, path_list->dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);
        /* Check if the builded path is executable */
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (full_path);
/* If not exec or doesn't exist, free memory and mv to nxt dirtry */
		free(full_path);
		path_list = path_list->next;
	}
	return (NULL);
}
/**
 * free_path_list - Frees a linked list of PATH directories
 * @head: The head of the linked list
 * This function iteratively frees each node of the linked list
 * starting from the head, ensuring that no memory is leaked.
 */
void free_path_list(path_t *head)
{
	path_t *temp;

/* Iterate through the list, freeing each directory node */
	while (head)
	{
		temp = head->next;
		free(head->dir); /* Freeing the directory string */
		free(head); /* Freeing the node itself */
		head = temp;
	}
}
