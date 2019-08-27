#include "shell.h"

/**
 * myhandle - signal handler
 * @mysignal: signal
 */
void myhandle(int mysignal)
{
	if (mysignal == SIGINT)
	{
		write(STDOUT_FILENO, "\n$ ", 3);
		fflush(stdout);
	}
}

/**
 * get_input - read a line of input
 * Return: pointer to input data (nul-terminated)
 * returns NULL when end of input is reached
 */
char *get_input(void)
{
	static char buf[5000];
	char *b = buf;
	size_t num = sizeof(buf);
	int linenum;
	int i = 0;
	static int exit_next_time;

	if (isatty(STDIN_FILENO))
		printf("$ ");

	if (exit_next_time)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		return (NULL);
	}

	linenum = getline(&b, &num, stdin);

	/* end of input */
	if (linenum == -1)
	{
		fflush(stdout);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}

	/* Check if input didn't end in \n */
	for (i = 0; buf[i]; i++)
		;
	if (i > 0 && buf[i - 1] != '\n')
		exit_next_time = 1;

	return (buf);
}
