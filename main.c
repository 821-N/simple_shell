#include "shell.h"

global g;

void executive(char **args, char *file_path, char **envp)
{
	pid_t parchild;

	parchild = fork();

	if (parchild < 0)
		printf("fail\n");

	else if (parchild == 0)
	{
		printf("child process, %s\n", args[0]);
		execve(file_path, args, envp);
	}
	wait(NULL);
}


int main(int argc, char **argv, char **env)
{
	char *input, **args, *file_path;
	char *path = get_env_var(env, "PATH");
	int i;
	char **envp = env;

	(void)argc;
	(void)argv;

	while (1)
	{
		printf("%d", g.c);
		signal(SIGINT, myhandle);
		signal(SIGTSTP, myhandle);

		/* display prompt and get input */
		input = get_input();
		if (input == NULL)
			return (0);

		/* get list of arguments from input */
		args = parse_input(input);
		//	print_args(args); /* debug */

		/* check if command is a builtin, and run it */
		if (!run_builtins(args))
		{
			/* check for alias and replace */
			do_alias(args);

			/* search for command in PATH */
			file_path = search_path(args[0], path);
			if (file_path)
			{
				printf("Found: %s\n", file_path);
				executive(args, file_path, envp);
			}
			else
				puts("Couldn't find");
		}

		g.c++;
  }
}
