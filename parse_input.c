#include "shell.h"

/**
 * parse_input - parse input command
 * @input: input
 * @var_list: env vars
 * Return: array of argument strings
 */
char **parse_input(char *input, VarList *var_list)
{
	static char *arglist[1000];
	int argi = 0; /* number of args */
	int quote = 0; /* if inside quoted section */
	char *start = NULL; /* start of arg being parsed */

	(void)var_list;
	for (; *input; input++)
	{
		if ((*input <= ' ' && !quote) || (*input == '"' && quote))
		{
			quote = 0;
			if (start)
			{
				*input = '\0';
				arglist[argi++] = start;
				start = NULL;
			}
		}
		else if (*input == '"')
		{
			quote = 1;
			if (!start)
				start = input + 1;
		}
		else
			if (!start)
				start = input;
	}
	if (start)
		arglist[argi++] = start;
	arglist[argi] = NULL;
	return (arglist);
}

/**
 * print_args - print arg list (for debug)
 * @args: arg list
 */
void print_args(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
		printf("Arg %d: `%s`\n", i, args[i]);
}
