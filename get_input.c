#include "shell.h"

void myhandle(int mysignal)
{
	if (mysignal == SIGINT)
	{
		write(STDOUT_FILENO, "\n$ ", 3);
		fflush(stdout);
		return;
	}	
	if (mysignal ==  SIGTSTP)
	{
	}
}

char *get_input(void)
{
	static char buf[5000], *b = buf;
	size_t num = 5000; 
	int linenum;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO,"$ ", 2);
	
	linenum = getline(&b, &num, stdin);
	/*printf("linenumber ---> %ld \n", linenum);*/
	
	/*printf("i == %d\n", i);*/
	if (linenum == -1)
	{
		fflush(stdout);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}

	return (buf);
}
