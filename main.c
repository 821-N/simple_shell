#include "shell.h"

global g;

int erro(int linenum, char *argv, char *com, int er_id)
{
	er_puts(argv);
	er_puts(": ");
	er_puts(itoa(linenum));
	er_puts(": ");
	er_puts(com);
	er_puts(": ");
	if (er_id == 0)
	{
		er_puts("not found\n");
		return (0);
	}
	return (0);
}

int builtin(char *args, char **ev)
{
	int i = 0, n = 0, it = 0, ex = 0;
	char *a = "exit env";

	while (a[n] != '\0' || args[i] != '\0')
	{
		if (a[n] == '\0')
			return (0);
		if (a[n] == ' ')
			it++;
		if (a[n] == args[i])
		{
			if (args[i] == '\0')
				break;
			i++;
			n++;
			if (a[n] == ' ')
			{
				i++;
				break;
			}
		}
		else
		{
			i = 0;
			n++;
		}
	}

	switch(it) {
		case 0:
			if (args[i] <= '9' && a[i] >= '0')
				ex = (args[i] - '0');
			else 
				exit(0);
			exit(ex);
		case 1:
			printenv(ev);
			return (1);
		default:
		return (0);
	}
	return (0);
}

void printenv(char **ev)
{
	int i = 0;

	while (*ev)
	{
		while (*ev[i])
			pchar(*ev[i++]);
		ev++;
	}
}

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

int main(int argc, char **argv, char **envp)
{
	char *input, **args, *file_path;
	char *env_path;
	int status,i = 0, n = 0;
	VarList variables;
	read_envp(&variables, envp);

	(void)argc;
	(void)argv;
  
	while (1)
	{
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

		if (args[0] == NULL)
			continue;

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
      {
				erro(g.c, argv[0], args[0], 0);
      }
    }
		g.c++;
  }
}
