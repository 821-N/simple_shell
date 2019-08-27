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

int put_error(char a);
int _strcmp(char *, char *);
int _atoi(char *a);
int erro(int linenum, char *argv, char *com, char *exstr, int er_id);
char *itoa(int i);
void er_puts(char *a);
int pchar(char a);
void _puts(char *a);
void printenv(VarList *);
int builtin(char *args, char **ev);
void myhandle(int mysignal);
char *get_input(void);
char **parse_input(char *, VarList *);
void print_args(char **);
int search_path(char *, char *, char **);
int run_builtins(char **args, char *shell, VarList *var_list, int lnum);
void do_alias(char **);

char *str(int, int);

void read_envp(VarList *, char **);
char **make_envp(VarList *);
void free_envp(char **envp);
void pid_envp(char **, pid_t);

void free_list(VarList *);
VarList *get_variable(VarList *, char *);
int remove_varible(VarList*, char *);
void set_variable(VarList*, char *, char *);

#endif
