#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *get_env_var(char **, char *);
char *get_input(void);

#endif
