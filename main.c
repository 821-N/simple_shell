#include "shell.h"

global g;

/**
 * str - convert a number to a string
 * @num: (should be "small", not INT_MAX or something silly)
 * Return: a malloc'd string, containing the decimal representation of @num
 */
char *str(int prefixlen, int num)
{
	int digits = 0, temp = num, sign = num < 0;
	char *str;

	while (temp)
	{
		digits++;
		temp /= 10;
	}
	str = malloc(prefixlen + sign + digits + 1);
	/* TODO: check if malloc failed */
	str[prefixlen + sign + digits] = '\0';
	if (sign)
	{
		num = -num;
		str[prefixlen] = '-';
	}
	while (--digits >= 0)
	{
		str[prefixlen + sign + digits] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

int executive(char **args, char *file_path, VarList *var_list)
{
	pid_t parchild;
	int status;
	char **envp;

	envp = make_envp(var_list);

	parchild = fork();
	if (parchild < 0)
		return (-1);

	if (parchild == 0)
	{
		printf("child process, %s\n", args[0]);
		status = execve(file_path, args, envp);
		_exit(status);
	}

	wait(&status);
	free_envp(envp);

	return (status);
}

void oh_no(int code)
{
	
	
}

int main(int argc, char **argv, char **envp)
{
	char *input, **args, *file_path;
	char *env_path;
	int status;
	VarList variables;

	read_envp(&variables, envp);

	(void)argc;
	(void)argv;

	while (1)
	{
		printf("%d", g.c);
		signal(SIGINT, myhandle);
		signal(SIGTSTP, myhandle);

		/* display prompt and get input */
		input = get_input();
		if (input == NULL) /* end of input reached */
		{
			free_list(&variables);
			dprintf(STDERR_FILENO,"exiting!");
			return (0);
		}

		/* get list of arguments from input */
		args = parse_input(input, &variables);
		//	print_args(args); /* debug */

		/* check if command is a builtin, and run it */
		if (!run_builtins(args, &variables))
		{
			/* otherwise ... */

			/* check for alias and replace */
			do_alias(args);

			/* search for command in PATH */
			env_path = get_variable(&variables, "PATH")->value;
			/* TODO: check if get_variable failed to find PATH */
			file_path = search_path(args[0], env_path);
			if (file_path)
			{
				printf("Found: %s\n", file_path);
				status = executive(args, file_path, &variables);
			}
			else
				puts("Couldn't find");
		}

		g.c++;
  }
}
