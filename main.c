#include "shell.h"


int main(int argc, char **argv, char **env)
{
	char *input, **args, *file_path, **sargs;
	char *path = get_env_var(env, "PATH");
	pid_t parchild;
	int hold, status, e;

	puts(path);
	while (1)
	{
		signal(SIGINT, myhandle);
		signal(SIGTSTP, myhandle);
		/* display prompt and get input */
		input = get_input();
		if (input == NULL)
			break;

//PLAN:
		/* get list of arguments from input */
		args = parse_input(input);
		print_args(args); /* debug */

		/* search for command in PATH */
		file_path = search_path(args[0], path);
		if (file_path)
			printf("Found: %s\n", file_path);
		else
			puts("Couldn't find");
		parchild = fork();
		if (parchild < 0)
			printf("fail\n");
		else if (parchild == 0)
		{
			execve(args[0], args, NULL);
		}
		
		/* run */
		//run_program(file_path, args, env);
	}
}
