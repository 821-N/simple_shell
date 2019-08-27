#include "shell.h"

/**
 * _copy - copies
 * @dest: what your copying into
 * @source: what your copying from
 * @length: the strlen
 * Return: pointer to dest
 */
char *_copy(char *dest, char *source, size_t length)
{
	while (length--)
		*dest++ = *source++;
	return (dest);
}

/**
 * _strcpy - copys
 * @dest: the destination
 * @source: the source
 * Return: void
 */
void _strcpy(char *dest, char *source)
{
	while((*dest++ = *source++))
		;
}

/**
 * _strchr - finding a char
 * @str: char in question
 * @c: char to find in str
 * Return: string
 */
char *_strchr(char *str, char c)
{
	for(; *str; str++)
	{
		if (*str == c)
			return (str);
	}
	return (NULL);
}

/**
 * search_path - searches path for program
 * @command: the command
 * @env_path: PATH
 * @filepath_out: pointer to file path output
 * Return: 0 (ok), 1 (file not found), 2 (permission error)
 */
int search_path(char *command, char *env_path, char **filepath_out)
{
	static char filepath[PATH_MAX];
	char *start = env_path;
	ssize_t path_length;
	int found_file = 0;

	if (command == NULL)
		return (2);
	/* If command contains a slash, don't check PATH */
	if (_strchr(command, '/'))
	{
		/* If file exists: */
		if (access(command, F_OK) == 0)
		{
			found_file = 1;
			/* If can be executed: */
			if (access(command, X_OK) == 0)
			{
				*filepath_out = command;
				return (0);
			}
		}
	}
	else
	{
		while (1)
		{
			if (*env_path == ':' || *env_path == '\0')
			{
				/* Copy PATH item and command into file_path */
				path_length = env_path - start;
				if (path_length)
				{
					_copy(filepath, start, path_length);
					filepath[path_length] = '/';
					path_length++;
				}
				_strcpy(filepath + path_length, command);
				/* Check file */
				if (access(filepath, F_OK) == 0)
				{
					found_file = 1;
					if (access(filepath, X_OK) == 0)
					{
						*filepath_out = filepath;
						return (0);
					}
				}
				/* reached end of PATH */
				if (*env_path == '\0')
					break;
				start = env_path + 1;
			}
			++env_path;
		}
	}

	/* If no file was found: */
	if (!found_file)
		return (1);
	/* Otherwise, if a file was found but couldn't be executed: */
	return (2);
}
