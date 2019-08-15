#include "shell.h"

int main(int argc, char **argv, char **env)
{
	char *input;
	char **args;
	char *file_path;

	while (1)
	{
		/* display prompt and get input */
		input = get_input();
		/* get list of arguments from input */
		args = parse_input(input);
		/* search for command in PATH */
		file_path = get_file(args[0]);
		/* run */
		run_program(file_path, args);
	}
}
