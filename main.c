#include "shell.h"

int main(int argc, char **argv, char **env)
{
	char *input;
	char **args;
	char *file_path;
	char *path = get_env_var(env, "PATH");
	puts(path);

	while (1)
	{
		/* display prompt and get input */
		input = get_input();
		if (input == NULL)
			break;

//PLAN:
		/* get list of arguments from input */
		args = parse_input(input);
		print_args(args); /* debug */
		/* search for command in PATH */
		//file_path = get_file(args[0], path);
		/* run */
		//run_program(file_path, args, env);
	}
}
