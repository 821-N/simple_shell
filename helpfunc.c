#include "shell.h"

/**
 * pchar - print char to stdout
 * @a: char
 * Return: output of write
 */
int pchar(char a)
{
	return (write(1, &a, 1));
}

/**
 * _puts - print string to stdout
 * @a: string
 */
void _puts(char *a)
{
	int i = 0;

	while (a[i])
		i++;

	write(STDOUT_FILENO, a, i);
}
