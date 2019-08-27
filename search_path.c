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
 * @av: argument
 * @lnum: linenumber
 * Return: filepath or NULL
 */
char *search_path(char *command, char *env_path, char *av, int lnum)
{
	static char filepath[PATH_MAX];
	char *start = env_path;
	ssize_t path_length;

	if (command == NULL)
		return (NULL);
	if (_strchr(command, '/'))
	{
		if (access(command, F_OK) != 0)
		{
			erro(lnum, av, command, NULL, 0);
			return (NULL);
		}
		if (access(command, X_OK) == 0)
			return (command);
		else
			erro(lnum, av, command, NULL, 1);
		return (NULL);
	}
	while (1)
	{
		if (*env_path == ':' || *env_path == '\0')
		{
			path_length = env_path - start;
			if (path_length)
			{
				_copy(filepath, start, path_length);
				filepath[path_length] = '/';
				path_length++;
			}
			_strcpy(filepath + path_length, command);
			if (access(command, F_OK) != 0 && *env_path == '\0')
			{
				erro(lnum, av, command, NULL, 0);
				return (NULL);
			}
			if (access(filepath, X_OK) == 0)
				return (filepath);
			else if (access(command, F_OK) == 0)
			{
				erro(lnum, av, command, NULL, 1);
				return (NULL);
			}
			if (*env_path == '\0')
				break; /* reached end without finding anything */
			start = env_path + 1;
		}
		++env_path;
	}
	return (NULL);
}
