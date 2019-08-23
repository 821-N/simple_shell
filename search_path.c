#include "shell.h"

char *_copy(char *dest, char *source, size_t length)
{
	while (length--)
		*dest++ = *source++;
	return (dest);
}

void _strcpy(char *dest, char *source)
{
	while((*dest++ = *source++))
		;
}

char *_strchr(char *str, char c)
{
	for(; *str; str++)
	{
		if (*str == c)
			return (str);
	}
	return (NULL);
}

char *search_path(char *command, char *env_path)
{
	static char filepath[4096];
	char *start = env_path;
	ssize_t path_length;

	/* If `command` contains a slash, don't check PATH: */
	if (command == NULL)
		return (NULL);
	if (_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (command);
		return (NULL);
	}
	/* Other wise, search PATH */
	while (1)
	{
		if (*env_path == ':' || *env_path == '\0')
		{
			/* Copy item from PATH, a slash, and `command` into `filepath` */
			path_length = env_path - start;
			if (path_length)
			{
				_copy(filepath, start, path_length);
				filepath[path_length] = '/';
				path_length++;
			}
			_strcpy(filepath + path_length, command);
			/* check */
			if (access(filepath, X_OK) == 0)
				return (filepath);
			if (*env_path == '\0')
				break; /* reached end without finding anything */
			start = env_path + 1;
		}
		++env_path;
	}
	return (NULL);
}
