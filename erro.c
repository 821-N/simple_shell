#include "shell.h"

int erro(int linenum, char *argv, char *com, int er_id)
{
	er_puts(argv);
	er_puts(": ");
	er_puts(itoa(linenum));
	er_puts(": ");
	er_puts(com);
	er_puts(": ");
	if (er_id == 0)
		er_puts("not found\n");
	else if(er_id == 1)
		er_puts("Permission denied\n");

	return (0);
}