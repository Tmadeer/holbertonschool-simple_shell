#ifndef MAIN_H
#define MAIN_H

#define MAX_ARGS 64

/* Standard C Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* UNIX System Calls */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Helpers / Parsing */
int tokenize_line(char *line, char *args[]);
int execute_command(char *cmd_path, char *args[], char **av);

/* Path operations */
char *get_path(void);
char *find_path(char *command);
char *resolve_command(char *command);

/* Built-in management */
int print_env(void);
int handle_builtin(char *args[], char *line, int *exit_status);

#endif /* MAIN_H */

