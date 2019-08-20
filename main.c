#include "shell.h"

global g;

int builtin(char *args, char **ev)
{
	int i = 0, n = 0;
	char **a;
	a[0] = "exit";
	a[1] = "env";

	while (a[n] != NULL)
	{
		i == 0;
		while (args[i] == a[n][i])
		{
			printf("%c | %c", args[i], a[n][i]);
			i++;
			if (a[n][i] == '\0' && a[n][i] == args[i])
				break;
		}
		n++;
	}

	switch(n) {
		case 1:
			exit(0);
		case 2:
			printenv(ev);
			return (1);
	}
	return (0);
}

void printenv(char **ev)
{
	int i = 0;

	while (*ev)
	{
		while (*ev[i])
		{
			putchar(*ev[i++]);
		}
		ev++;
	}
}


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
	int hold, status, e, i = 0;
	char **envp = env;

	puts(path);
	while (1)
	{
		printf("%d", g.c);
		signal(SIGINT, myhandle);
		signal(SIGTSTP, myhandle);
		/* display prompt and get input */
		input = get_input();
		if (input == NULL)
			return (0);
		else
		{
			while (input[i])
				i++;
			if (input[i - 1] != '\n' )
				break;
//PLAN:		
			if (builtin(input, envp))
			{

				/* get list of arguments from input */
				args = parse_input(input);
			//	print_args(args); /* debug */
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
			/* run */
			//run_program(file_path, args, env);
			g.c++;
			i = 0;
			
	    }
	}
}
