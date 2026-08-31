#include "main.h"

/**
 * get_path - Retrieves the value of PATH from environ
 *
 * Return: Pointer to PATH value, or NULL if not found
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
 * @command: The command name to search for
 *
 * Return: Full path if found (malloc'd), NULL if not found
 */
char *find_path(char *command)
{
	char *path_value, *path_copy, *dir, *result;
	char full_path[1024];
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
 * @command: The command typed by user
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

