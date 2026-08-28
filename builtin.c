#include "main.h"
/**
 * print_env - Prints the current environment, one variable per line
 *
 * Return: 1 (always, so the caller knows the built-in was handled)
 */
int print_env(void)
{
	int i;

	for (i = 0; environ && environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}
/**
 * handle_builtin - Checks if a command is a built-in and executes it
 * @args: Array of arguments (args[0] is the command name)
 * @line: The line read by getline (freed before exiting, only for "exit")
 * @exit_status: Pointer to the main's exit_status variable
 *
 * Return: 1 if the command was a built-in and was handled, 0 if not
 */
int handle_builtin(char *args[], char *line, int *exit_status)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(*exit_status);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		return (print_env());
	}
	return (0);
}
