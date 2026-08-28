#include "main.h"
/**
 * get_path - Retrieves the value of PATH from environ
 *
 * Return: Pointer to PATH value (not malloc'd), or NULL if not found
 */
char *get_path(void)
{
	int i;
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}
/**
 * find_path - Searches PATH directories for an executable command
 * @command: The command name to search for (e.g. "ls")
 *
 * Return: Full path if found (malloc'd), NULL if not found
 */
char *find_path(char *command)
{
	char *path_value;
	char *path_copy;
	char *dir;
	char full_path[1024];
	char *result;
	size_t path_len;
	path_value = get_path();
	if (path_value == NULL)
		return (NULL);
	path_len = strlen(path_value);
	path_copy = malloc(path_len + 1);
	if (path_copy == NULL)
		exit(EXIT_FAILURE);
	strcpy(path_copy, path_value);
	for (dir = strtok(path_copy, ":"); dir != NULL; dir = strtok(NULL, ":"))
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			result = malloc(strlen(full_path) + 1);
			if (result == NULL)
				exit(EXIT_FAILURE);
			strcpy(result, full_path);
			free(path_copy);
			return (result);
		}
	}
	free(path_copy);
	return (NULL);
}
/**
 * resolve_command - Determines the full path to execute for a command
 * @command: The command as typed by the user (e.g. "ls" or "./hbtn_ls")
 *
 * Return: Full path if executable found (malloc'd), NULL if not found
 */
char *resolve_command(char *command)
{
	char *result;
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
		{
			result = malloc(strlen(command) + 1);
			if (result == NULL)
				exit(EXIT_FAILURE);
			strcpy(result, command);
			return (result);
		}
		return (NULL);
	}
	return (find_path(command));
}
/**
 * tokenize_line - Splits a line into an array of arguments by whitespace
 * @line: The input line to split (will be modified by strtok)
 * @args: Array to store the resulting argument pointers
 *
 * Return: Number of tokens found
 */
int tokenize_line(char *line, char *args[])
{
	int i = 0;
	char *token;
	token = strtok(line, " \t\n");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (i);
}
/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Exit status of last command, or 127 if command not found
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	char *args[MAX_ARGS];
	pid_t child_pid;
	int token_count;
	char *cmd_path;
	int line_number = 0;
	int exit_status = 0;
	(void)ac;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
		line_number++;
		token_count = tokenize_line(line, args);
		if (token_count == 0)
			continue;
		if (handle_builtin(args, line, &exit_status))
			continue;
		cmd_path = resolve_command(args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", av[0], line_number, args[0]);
			exit_status = 127;
			continue;
		}
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(cmd_path, args, environ) == -1)
			{
				perror(av[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&exit_status);
			exit_status = WEXITSTATUS(exit_status);
		}
		free(cmd_path);
	}
	free(line);
	return (exit_status);
}

