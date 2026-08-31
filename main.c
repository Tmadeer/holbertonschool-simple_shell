#include "main.h"

/**
 * main - Entry point for the simple shell
 * @ac: Argument count (unused)
 * @av: Argument vector
 *
 * Return: Exit status of last command, or 127 if command not found
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	char *args[MAX_ARGS];
	char *cmd_path;
	int line_number = 0, exit_status = 0;

	(void)ac;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		if (getline(&line, &len, stdin) == -1)
			break;

		line_number++;
		if (tokenize_line(line, args) == 0)
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

		exit_status = execute_command(cmd_path, args, av);
		free(cmd_path);
	}
	free(line);
	return (exit_status);
}

