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
	int line_num = 0;
	char *input, **args, *file_path, *env_path;
	VarList variables;
	int status;

	read_envp(&variables, envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		line_num++;
		signal(SIGINT, myhandle);
		signal(SIGTSTP, myhandle);
		input = get_input();
		if (input == NULL) /* end of input reached */
		{
			free_list(&variables);
			return (0);
		}
		args = parse_input(input, &variables);
		if (args[0] == NULL)
			continue;
		if (!run_builtins(args, &variables, envp, argv[0], line_num))
		{
			/*do_alias(args);*/
			env_path = get_variable(&variables, "PATH")->value;
			status = search_path(args[0], env_path, &file_path);
			if (status == 0)
				executive(args, file_path, &variables);
			else
				erro(line_num, argv[0], args[0], NULL, status - 1);
		}
	}
	return (0);
}
