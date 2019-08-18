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
	char *input, **args, *file_path, **sargs;
	char *path = get_env_var(env, "PATH");
	int hold, status, e;
	char **envp = env;


	puts(path);
	while (1)
	{
		printf("%d", g.c);
		/* display prompt and get input */
		input = get_input();
		if (input)
		{
			//printf("input = %s\n", input);
			signal(SIGINT, myhandle);
			signal(SIGTSTP, myhandle);
//PLAN:
		/* get list of arguments from input */

			args = parse_input(input);
			print_args(args); /* debug */
			
		/* search for command in PATH */
			file_path = search_path(args[0], path);
			printf(":)\n");
			if (file_path)
			{
			//	printf("Found: %s\n", file_path);
				executive(args, file_path, envp);
			}
			else
				puts("Couldn't find");
		
		/* run */
		//run_program(file_path, args, env);
		}
		else if (input == NULL)
		{
			printf("lol\n");
			break;
		}
		g.c++;
	}
	return (0);
}
