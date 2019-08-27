#include "shell.h"

/**
 * printenv - prints the enviroment
 * @ev: the enviroment
 * Return: void
 */
void printenv(char **ev)
{
	int i = 0;


	while (ev[i])
	{
		_puts(ev[i]);
		pchar('\n');
		i++;
	}
}

/**
 * str - convert a number to a string
 * @num: (should be "small", not INT_MAX or something silly)
 * @prefixlen: first number
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

/**
 * executive - runs the programs after the search_path
 * @args: the tokenized arguments from getline
 * @file_path: the file path of the program
 * @var_list: the VarList
 * Return: the status of the fork
 */
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

/**
 * main - the main shell
 * @argc: the number of arguments
 * @argv: the arguments
 * @envp: the enviroment
 * Return: 0
 */
int main(int argc, char **argv, char **envp)
{
	global g;
	char *input, **args, *file_path, *env_path;
	VarList variables;

	read_envp(&variables, envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		g.c++;
		signal(SIGINT, myhandle);
		signal(SIGTSTP, myhandle);
		input = get_input();
		if (input == NULL) /* end of input reached */
		{
			free_list(&variables);
			dprintf(STDERR_FILENO, "exiting!");
			return (0);
		}
		args = parse_input(input, &variables);
		if (args[0] == NULL)
			continue;
		if (!run_builtins(args, &variables, envp, argv[0], g.c))
		{
			/*do_alias(args);*/
			env_path = get_variable(&variables, "PATH")->value;
			file_path = search_path(args[0], env_path, argv[0], g.c);
			if (file_path)
			{
				printf("Found: %s\n", file_path);
				executive(args, file_path, &variables);
			}
		}
	}
	return (0);
}
