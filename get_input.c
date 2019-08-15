#include "shell.h"
static char buf[5000], *b = buf;
ssize_t num = 5000, linenum;

char *get_input(void)
{
	if (isatty(STDIN_FILENO))
		printf("$ ");
	linenum = getline(&b, &num, stdin);
	if (linenum == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		return (NULL);
	}
	return (buf);
}
