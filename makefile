CC=gcc
CFLAGS=-Wextra -Wall -pedantic -Wno-unused-parameter

shell: main.o search_path.o get_input.o parse_input.o alias.o builtins.o variables.o envp.o
	$(CC) $(CFLAGS) main.o search_path.o get_input.o parse_input.o alias.o builtins.o variables.o envp.o
