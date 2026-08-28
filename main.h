#ifndef MAIN_H
#define MAIN_H


#define MAX_ARGS 64
/* Standard C Libraries for I/O, memory, and strings */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* UNIX System Calls for process management */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */
extern char **environ;
int tokenize_line(char *line, char *args[]);
char *get_path(void);
char *find_path(char *command);
char *resolve_command(char *command);
int handle_builtin(char *args[], char *line, int *exit_status);

#endif /* MAIN_H */
