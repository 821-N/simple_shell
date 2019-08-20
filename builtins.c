#include "shell.h"

int run_builtins(char **args, VarList *var_list)
{
	VarList *item;

	if (args[0] == NULL)
		return (0);

	if (!_strcmp(args[0], "pv"))
	{
		item = get_variable(var_list, args[1]);
		if (item)
			printf("%s\n", item->value);
		else
			printf("variable not found\n");
		return (1);
	}
	if (!_strcmp(args[0], "setenv"))
	{
		if (args[1] && args[2])
			set_variable(var_list, args[1], args[2]);
		return (1);
	}

	return (0);
}
