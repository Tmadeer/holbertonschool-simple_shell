#include "main.h"

extern char **environ;

/**
 * trim_line - Removes leading and trailing spaces/tabs from a string
 * @line: The string to trim (modified in place)
 *
 * Return: Pointer to the start of the trimmed string
 */
char *trim_line(char *line)
{
	char *start = line;
	char *end;

	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
		return (start);

	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';

	return (start);
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
	char *trimmed;
	size_t len = 0;
	size_t len_line;
	char *args[2];
	pid_t child_pid;

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

		trimmed = trim_line(line);
		if (trimmed[0] == '\0')
			continue;

		args[0] = trimmed;
		args[1] = NULL;

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
