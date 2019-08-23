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

void er_puts(char *a)
{
	int i = 0;

	while (a[i])
		i++;

	write(STDERR_FILENO, a, i);	
}

int put_error(char a)
{
	return (write(STDERR_FILENO, &a, 1));
}

char *itoa(int i)
{
	char a[500], b[500], *buf = b;
	int n = 0, x = 0, save = i;

	if (i == 0)
		return ("0");
	while (i)
	{
		a[n] = ((i % 10) + '0');
		i /= 10;
		n++;
	}
	if (save < 10)
	{
		buf = a;
		return (buf);
	}
	n--;
	while (0 <= n)
	{
		b[x] = a[n];
		x++;
		n--;
	}
	return (buf);
}