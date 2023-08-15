#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>

#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"
#define EXECUTION_ERROR 127

/***/
typedef struct PathNode {
	char *dir;
	struct PathNode *next;
} PathNode;

void init_token(void);
void check_allocation(void *ptr);
void resize_token_buffer(void);
char *parse_input(void);
void parse_path(const char *path, PathNode **path_list);
char *search_path(const char *cmd, PathNode *path_list);
void free_path_list(PathNode *path_list);
char *_getenv(const char *name);
void direct_execute(char *cmd);
void path_execute(char *cmd, char **args, PathNode *path_list);
void execute_command(char *cmd, PathNode *path_list);
void main_loop(void);
char **tokenize(char *line);
void direct_execute_args(char *cmd, char **args);
void print_error(const char *command, const char *message);

#endif
