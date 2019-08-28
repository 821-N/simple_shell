# 0x16. C - Simple Shell
This is the readme for the sh

			                _____
			| |     | |    / ___ \    | |     | |
			| |     | |   / /   \_\   | |     | |
			| |_____| |   \ \____     | |_____| |
			|  _____  |    \____ \    |  _____  |
			| |     | |   __    \ \   | |     | |
			| |     | |   \ \___/ /   | |     | |
			| |     | |    \_____/    | |     | |

## NAME

hsh - Holberton Simple Shell command interpreter (shell)


## SYNOPSIS

./hsh

[command] [arguments ...]

## DESCRIPTION

We create a shell called hsh. We made it closely resemble sh.

## COMPILE WITH

    gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

## Built-ins

 1. exit - to exit the shell.
 2. env - prints  environment.
 3. cd - change directory

## Example
	your@shell:$ ./hsh
	(hsh)$ ls
	file1 file2 executable /dir/
	(hsh)$

## Contents of repository
|  Files| Description|
|--|--|
|variable.c| works with variables|
|get_input.c| this function allows for shell to recieve input from stdin|
|search_path.c|function looks through the path and checks if command from stdin is a real command. |
|parse_input| tokanizer for input from stdin|
|main.c|main file for shell|
|builtins.c|Contains built-ins for the shell. Function for the env built-in can be found in hsh.c|
|error.c| Handles errors for the shell |
|envp.c| works with the enviroment |
|helpfunc.c  | Contains helper functions that we built ourselves (atoi, itoa, _puts, pchar etc) |
|shell.h|header file containing global variables and the libraries for the functions we used|

## Author
Contributor(s) to the Holberton Shell project
 - Christian Williams
 - Nathaniel Marofsky