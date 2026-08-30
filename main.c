#include "main.h"
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
