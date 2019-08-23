#ifndef SHELL_H
#define SHELL_H

typedef struct global
{
	int c;
} global;

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int pchar(char a);
void _puts(char *a);
void printenv(char **ev);
int builtin(char *args, char **ev);
void myhandle(int mysignal);
char *get_env_var(char **, char *);
char *get_input(void);
char **parse_input(char *);
void print_args(char **);
char *search_path(char *, char *);

#endif
