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

/**
 * builtin_setenv - setenv builtin command
 * @args: arguments (command is args[0])
 * @shell: name of shell executable
 * @var_list: environment variables
 * @lnum: line number
 * Return: exit code
 */
int builtin_setenv(char **args, char *shell, VarList *var_list, int lnum)
{
	if (!args[1] || !args[2] || args[3])
	{
		return (erro(lnum, shell, args[0], "VARIABLE VALUE", 3));
	}
	set_variable(var_list, args[1], args[2]);
	return (0);
}

/**
 * builtin_unsetenv - unsetenv builtin command
 * @args: arguments (command is args[0])
 * @shell: name of shell executable
 * @var_list: environment variables
 * @lnum: line number
 * Return: exit code
 */
int builtin_unsetenv(char **args, char *shell, VarList *var_list, int lnum)
{
	if (!args[1] || args[2])
	{
		return (erro(lnum, shell, args[0], "VARIABLE", 3));
	}
	remove_variable(var_list, args[1]);
	return (0);
}

/**
 * run_builtins - try to run command as a builtin
 * @args: arguments (command is args[0])
 * @shell: name of shell executable
 * @var_list: environment variables
 * @lnum: line number
 * Return: 0 (no builtin), 1 (builtin ran), -1 (exit)
 */
int run_builtins(char **args, char *shell, VarList *var_list, int lnum, int *ec)
{
	int i = 0;

	*ec = 0;

	if (!_strcmp(args[0], "setenv"))
	{
		*ec = builtin_setenv(args, shell, var_list, lnum);
		return (1);
	}
	if (!_strcmp(args[0], "unsetenv"))
	{
		*ec = builtin_unsetenv(args, shell, var_list, lnum);
		return (1);
	}

	if (!_strcmp(args[0], "env"))
	{
		printenv(var_list);
		return (1);
	}

	if (!_strcmp(args[0], "exit"))
	{
		if (args[1])
			i = parse_number(args[1]);
		else
			i = 0;
		if (i >= 0)
		{
			*ec = i;
			return (-1);
		}
		else
			erro(lnum, shell, args[0], args[1], 2);
		return (1);
	}

	return (0);
}
