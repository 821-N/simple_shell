#include "shell.h"

/**
 * parse_number - read a string containing a non-negative number
 * @a: string
 * Return: number, or -1 if @a is not a valid number
 */
int parse_number(char *a)
{
	int i, num = 0;

	if (a == NULL)
		return (-1);
	for (i = 0; a[i]; i++)
	{
		if (a[i] >= '0' && a[i] <= '9')
			num = num * 10 + (a[i] - '0');
		else
			return (-1);
	}
	return (num);
}

void builtin_setenv(char **args, char *shell, VarList *var_list, int lnum)
{
	if (!args[1] || !args[2] || args[3])
	{
		erro(lnum, shell, args[0], "VARIABLE VALUE", 3);
		return;
	}
	set_variable(var_list, args[1], args[2]);
}

void builtin_unsetenv(char **args, char *shell, VarList *var_list, int lnum)
{
	if (!args[1] || args[2])
	{
		erro(lnum, shell, args[0], "VARIABLE", 3);
		return;
	}
	remove_variable(var_list, args[1]);
}

/**
 * run_builtins - try to run command as a builtin
 * @args: arguments (command is args[0])
 * @shell: name of shell executable
 * @var_list: environment variables
 * @lnum: line number
 * Return: -2 (no builtin found), -1 (builtin found), other (exit code)
 */
int run_builtins(char **args, char *shell, VarList *var_list, int lnum)
{
	int i = 0;

	if (args[0] == NULL)
		return (-2);

	if (!_strcmp(args[0], "setenv"))
	{
		builtin_setenv(args, shell, var_list, lnum);
		return (-1);
	}
	if (!_strcmp(args[0], "unsetenv"))
	{
		builtin_unsetenv(args, shell, var_list, lnum);
		return (-1);
	}

	if (!_strcmp(args[0], "env"))
	{
		printenv(var_list);
		return (-1);
	}

	if (!_strcmp(args[0], "exit"))
	{
		if (args[1])
			i = parse_number(args[1]);
		else
			i = 0;
		if (i >= 0)
			return (i);
		erro(lnum, shell, args[0], args[1], 2);
		return (-1);
	}

	return (-2);
}
