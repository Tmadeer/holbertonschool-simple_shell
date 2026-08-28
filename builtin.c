#include "main.h"
/**
 * handle_builtin - Checks if a command is a built-in and executes it
 * @args: Array of arguments (args[0] is the command name)
 * @line: The line read by getline (freed before exiting)
 * @exit_status: Pointer to the main's exit_status variable
 *
 * Return: 1 if the command was a built-in (never actually returns for
 * "exit" since the process terminates), 0 if not a built-in
 */
int handle_builtin(char *args[], char *line, int *exit_status)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(*exit_status);
	}
	return (0);
}

