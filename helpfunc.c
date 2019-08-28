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

/**
 * safe_malloc - tries to alloc memory and exits if fails
 * @size: number of bytes
 * Return: pointer to allocated memory
 */
void *safe_malloc(size_t size)
{
	void *x = malloc(size);

	if (!x)
	{
		er_puts("Failed to allocate memory!\n");
		exit(1);
	}
	return (x);
}
/**
 * err_vaputs - prints many strings out to stderr
 * @dnothing: does nothing yet
 * Return: void
 */
void err_vaputs(int dnothing, ...)
{
	va_list args;
	char *print;

	va_start(args, dnothing);
	while (dnothing > 0)
	{
		print = va_arg(args, char *);
		if (print == NULL)
			break;
		er_puts(print);
		dnothing--;
	}
	va_end(args);
}
