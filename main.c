#include "main.h"

/**
 * find_path - Searches PATH directories for an executable command
 * @command: The command name to search for (e.g. "ls")
 *
 * Return: Full path if found (malloc'd), NULL if not found
 */
char *find_path(char *command)
{
	char *path_value = getenv("PATH");
	char *path_copy;
	char *dir;
	char full_path[1024];
	char *result;
	size_t path_len;

	if (path_value == NULL)
		return (NULL);

	path_len = strlen(path_value);
	path_copy = malloc(path_len + 1);
	if (path_copy == NULL)
		exit(EXIT_FAILURE);
	strcpy(path_copy, path_value);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
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
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * tokenize_line - Splits a line into an array of arguments by spaces/tabs/newlines
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
 * Return: Always 0 on success
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	char *args[MAX_ARGS];
	pid_t child_pid;
	int token_count;
	char *cmd_path;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		if (getline(&line, &len, stdin) == -1)
			break;

		token_count = tokenize_line(line, args);
		if (token_count == 0)
			continue;

		cmd_path = find_path(args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
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
			wait(NULL);
		}
		free(cmd_path);
	}

	free(line);
	return (0);
}
