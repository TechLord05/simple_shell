#include "shell.h"

/**
 * builtin - Check if a command is a built-in shell command.
 * @av: The command to check.
 *
 * Return: No return value.
 */
void builtin(char **av)
{
	if (av == NULL || av[0] == NULL)
		return;

	else if (_strcmp(av[0], "exit") == 0)
	{
		execute_exit_command(av[1]);
	}
	else if (_strcmp(av[0], "env") == 0)
	{
		if (isatty(1))
		{
			_env();
		}
	}
}

/**
 * _env - Print the environment variables.
 *
 * This function prints the environment variables to the standard output.
 *
 * Return: Always 0.
 */
int _env(void)
{
	int i;
	char **_environ;

	for (i = 0; environ[i]; i++)
		;

	_environ = malloc(sizeof(char *) * (i + 1));
	if (_environ == NULL)
	{
		perror("malloc");
		return (1);
	}

	for (i = 0; environ[i]; i++)
		_environ[i] = _strdup(environ[i]);
	_environ[i] = NULL;

	for (i = 0; _environ[i]; i++)
	{
		write(STDOUT_FILENO, _environ[i], _strlen(_environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(_environ);
	return (0);
}

/**
 * execute_exit_command - Execute the "exit" built-in command.
 * @av: The exit argument (optional).
 */
void execute_exit_command(char *av)
{
	if (av == NULL)
		is_exit("exit", NULL);
	else
		is_exit("exit", av);
}

/**
 * Change_Directory - This function changes the current working directory.
 *
 * @path: The path of the directory to change to.
 *
 * */
void Change_Directory(const char *path)
{
	char cwd[BUFFER_SIZE];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd: Failed to get current working directory");
		return;
	}

	if (setenv("PWD", cwd, 1) != 0)
	{
		perror("cd: Failed to update PWD environment variable");
		return;
	}

	if (chdir(path) != 0)
	{
		perror("cd: Failed to change directory");
		return;
	}
}
