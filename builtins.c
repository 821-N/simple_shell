#include "shell.h"

int run_builtins(char **args, VarList *var_list, char **ev, char *av, int lnum)
{
	int i = 0;
	/*VarList *item;*/

	if (args[0] == NULL)
		return (0);
	if (!_strcmp(args[0], "setenv"))
	{
		if (args[1] && args[2])
			set_variable(var_list, args[1], args[2]);
		return (1);
	}

	if (!_strcmp(args[0], "env"))
	{
		printenv(ev);
		return (1);
	}

	if (!_strcmp(args[0], "exit"))
	{
		if (args[1])
		{
			printf("args 1 %s\n", args[1]);
			while (args[1][i])
			{
				if ((args[1][i] > '9' || args[1][i] < '0') && args[1][i] != '\0')
				{	
					erro(lnum, av, args[0], args[1], 2);
					return (1);
				}
				i++;
			}
			exit(_atoi(args[1]));
		}
		exit(0);
	}
	return (0);
}
