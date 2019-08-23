#include "shell.h"

int pchar(char a)
{
	return (write(1, &a, 1));
}

void _puts(char *a)
{
	int i = 0;

	while (a[i])
		i++;

	write(STDOUT_FILENO, a, i);	
}