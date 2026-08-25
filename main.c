#include "main.h"

extern char **environ;

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
		if (line[0] == '\0')
			continue;
		args[0] = line;
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
