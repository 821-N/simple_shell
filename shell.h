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
#include <limits.h>

typedef struct VarList {
	struct VarList *next;
	union {
		struct {
			char *name;
			char *value;
		};
		size_t length;
	};
} VarList;

void myhandle(int mysignal);
char *get_input(void);
char **parse_input(char *);
void print_args(char **);
char *search_path(char *, char *);
int run_builtins(char **);
void do_alias(char **);

void read_envp(VarList *, char **);
char **make_envp(VarList *);
void free_envp(char **envp);

void free_list(VarList *);
VarList *get_variable(VarList *, char *);
int remove_varible(VarList*, char *);
void set_variable(VarList*, char *, char *);

#endif
