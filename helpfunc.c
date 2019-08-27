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
	static char a[500], b[500], *buf = b;
	int n = 0, x = 0;

	if (i == 0)
		return ("0");
	while (i)
	{
		a[n] = ((i % 10) + '0');
		if (i < 10)
			break;
		i /= 10;
		n++;
	}
	while (0 <= n)
	{
		b[x] = a[n];
		x++;
		n--;
	}
	b[x] = '\0';
	return (buf);
}

int _atoi(char *a)
{
	int i = 0, x = 1, n = 0, sum = 0;

	while (a[i] <= '9' && a[i] >= '0')
	{
		i++;
		if (a[i] <= '9' && a[i] >= '0') 
			x *= 10;
	}
	while (n < i)
	{
		sum += x * (a[n] - '0');
		x /= 10;
		n++;
	}
	if (i)
		return (sum);

	return (0);
}