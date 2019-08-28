#include "shell.h"

/**
 * er_num - print number to stderr
 * @num: number to print. Should not be INT_MIN
 */
void er_num(int num)
{
	char buffer[10];
	int bufp = 10;

	while (num)
	{
		buffer[--bufp] = num % 10 + '0';
		num /= 10;
	}
	write(STDERR_FILENO, buffer + bufp, 10 - bufp);
}

/**
 * er_puts - print string to stderr
 * @a: string
 */
void er_puts(char *a)
{
	int len = 0;

	if (a == NULL)
		return;
	while (a[len])
		len++;
	write(STDERR_FILENO, a, len);
}

/**
 * erro - print error message
 * @linenum: line number
 * @argv: name of shell executable
 * @com: command
 * @exstr: argv 1
 * @er_id: error id
 * Return: exit code
 */
int erro(int linenum, char *argv, char *com, char *exstr, int er_id)
{
	err_vaputs(2, argv, ": ");
	er_num(linenum);
	err_vaputs(3, ": ", com, ": ");
	if (er_id == 0)
	{
		er_puts("not found\n");
		return (127);
	}
	else if (er_id == 1)
	{
		er_puts("Permission denied\n");
		return (126);
	}
	else if (er_id == 2)
	{
		err_vaputs(3, "Illegal number: ", exstr, "\n");
		if (isatty(STDIN_FILENO))
			return (2);
		exit(2);
	}
	else if (er_id == 3)
	{
		err_vaputs(4, "Usage: ", com, " ", exstr, "\n");
		return (1);
	}
	else if (er_id == 4)
	{
		err_vaputs(3, "can't cd to ", exstr, "\n");
		if (isatty(STDIN_FILENO))
			return (2);
		exit(2);
	}
	return (0);
}
