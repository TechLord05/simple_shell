#include "shell.h"

/**
 * _setenv - sets an environment variable
 * @name: name of the variable
 * @value: value of the variable
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value)
{
	int length = 0;
	char *new_string = NULL;

	length = _strlen(name) + _strlen(value) + 2;
	new_string = malloc(sizeof(char) * length);

	if (new_string == NULL)
	{
		write(STDERR_FILENO, "Error: malloc failed\n", 21);
		return (-1);
	}

	_strcpy(new_string, name);
	_strcat(new_string, "=");
	_strcat(new_string, value);

	/*inilialze a new environment or modify existing one*/
	if (_putenv(new_string) != 0)
	{
		write(STDERR_FILENO, "Error: _putenv failed\n", 21);
		free(new_string);
		return (-1);
	}
	return (0);
}


/**
 * _putenv - adds or changes the value of an environment variable
 * @string: string of the form name=value
 * Return: 0 on success, 1 on failure
 */
int _putenv(char *string)
{
	int i;
	char *delimeter, **new_environ;

	delimeter = _strchr(string, '=');
	if (string == NULL || delimeter == NULL || delimeter == string)
	{
		write(STDERR_FILENO, "Error: invalid argument\n", 24);
		return (1);
	}
	/*check if variable exit*/
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(string, environ[i], delimeter - string + 1) == 0)
		{
			environ[i] = string;
			return (0);
		}
	}
	/*if variable doesn't exit*/
	while (environ[i] != NULL)
		i++;
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (new_environ == NULL)
	{
		perror("malloc");
		return (1);
	}
	for (i = 0; environ[i] != NULL; i++)
		new_environ[i] = environ[i];
	new_environ[i] = string;
	new_environ[i + 1] = NULL;
	environ = new_environ;
	return (0);
}

/**
 * _unsetenv - unsets an environment variable
 * @name: name of the variable
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	int z, q, length = 0;
	int environ_len = 0, found = 0;
	char **new_environ = NULL;

	length = _strlen(name);
	while (environ[environ_len] != NULL)
		environ_len++;

	for (z = 0; environ[z] != NULL; z++)
	{
		if (strncmp(environ[z], name, length) == 0)
		{
			found = 1;
			free(environ[z]);
			for (q = z; environ[q] != NULL; q++)
				environ[q] = environ[q + 1];
			environ_len--;
			break;
		}
	}

	/*if not found return 0*/
	if (found == 0)
		return (0);
	new_environ = malloc(sizeof(char *) * (environ_len + 1));
	if (new_environ == NULL)
	{
		write(STDERR_FILENO, "Error: malloc- failed\n", 21);
		return (-1);
	}

	for (z = 0; environ[z] != NULL; z++)
		new_environ[z] = environ[z];
	new_environ[z] = NULL;

	free(environ);
	environ = new_environ;
	return (0);
}
