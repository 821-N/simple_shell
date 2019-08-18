#include "shell.h"

void myhandle(int mysignal)
{
	if (mysignal == SIGINT)
	{
		printf("\n$ ");
		fflush(stdout);
		return;
	}	
	if (mysignal ==  SIGTSTP)
		;
}

char *get_input(void)
{
	static char buf[5000], *b = buf;
	ssize_t num = 5000, linenum;

	if (isatty(STDIN_FILENO))
		printf("$ ");
	
	linenum = getline(&b, &num, stdin);
//	printf("linenumber ---> %ld\n", linenum);
	if (linenum == -1)
	{
		fflush(stdout);
		if (isatty(STDIN_FILENO))
			printf("\n");
		return (NULL);
	}
	return (buf);
}
