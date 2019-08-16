CC=gcc
CFLAGS=-Wextra -Wall -pedantic

shell: main.o search_path.o get_input.o get_env_var.o parse_input.o
	$(CC) $(CFLAGS) main.o search_path.o get_input.o get_env_var.o parse_input.o
