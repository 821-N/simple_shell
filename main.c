#include "shell.h"

global g;

int errono()
{
	
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


void executive(char **args, char *file_path, char **envp)
{
	pid_t parchild;

	parchild = fork();

	if (parchild < 0)
		exit(0);
		//printf("fail\n");

	else if (parchild == 0)
	{
		//printf("child process, %s\n", args[0]);
		execve(file_path, args, envp);
	}
	wait(NULL);
}


int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	char *input, **args, *file_path, *path = get_env_var(env, "PATH");
	int i = 0, n = 0;
	char **envp = env;
	
	//puts(path);
	while (1)
	{
		signal(SIGINT, myhandle);
		signal(SIGTSTP, myhandle);
		input = get_input();
		if (input == NULL)
			return (0);
		else
		{
			while (input[i])
				i++;
			if (input[i - 1] != '\n')
			{
				write(STDOUT_FILENO, "\n$ \n", 4);
				break;
			}
			args = parse_input(input);
			file_path = search_path(args[0], path);
			if (file_path)
				executive(args, file_path, envp);
			else
			{
				n = 0;
				while (input[n++] == ' ')
					;
				if (!(builtin(input, envp)) && n != i)
					_puts("Couldn't find\n");
			}
		}
		g.c++;
		i = 0;
	}
	return (0);
}
