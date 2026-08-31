#include "main.h"

/**
 * tokenize_line - Splits a line into an array of arguments by whitespace
 * @line: The input line to split
 * @args: Array to store argument pointers
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
 * execute_command - Forks and executes the command with execve
 * @cmd_path: Full path of the executable
 * @args: Arguments array
 * @av: Program invocation arguments
 *
 * Return: Exit status of the executed command
 */
int execute_command(char *cmd_path, char *args[], char **av)
{
	pid_t child_pid;
	int status = 0;

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
		wait(&status);
		status = WEXITSTATUS(status);
	}
	return (status);
}
