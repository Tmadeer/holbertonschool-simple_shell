#include "main.h"

extern char **environ;

/**
 * tokenize_line - Splits a line into an array of arguments by spaces/tabs
 * @line: The input line to split (will be modified by strtok)
 * @args: Array to store the resulting argument pointers
 *
 * Return: Number of tokens found
 */
int tokenize_line(char *line, char *args[])
{
	int i = 0;
	char *token;

	token = strtok(line, " \t");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t");
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
	size_t len_line;
	char *args[MAX_ARGS];
	pid_t child_pid;
	int token_count;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		if (getline(&line, &len, stdin) == -1)
			break;

		len_line = strlen(line);
		if (len_line > 0 && line[len_line - 1] == '\n')
			line[len_line - 1] = '\0';

		token_count = tokenize_line(line, args);
		if (token_count == 0)
			continue;

		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror(av[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	free(line);
	return (0);
}
