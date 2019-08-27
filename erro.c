#include "shell.h"
/**
 * erro - the error
 * linenum: line number
 * argv: first argument from 
 * com: command
 * exstr: argv 1
 * er_id: error id
 * return: error num or 0
 */
int erro(int linenum, char *argv, char *com, char *exstr, int er_id)
{
	er_puts(argv);
	er_puts(": ");
	er_puts(itoa(linenum));
	er_puts(": ");
	er_puts(com);
	er_puts(": ");
	if (er_id == 0)
	{
		er_puts("not found\n");
		return (127);
	}
	else if(er_id == 1)
	{
		er_puts("Permission denied\n");
		return (126);
	}
	else if(er_id == 2)
	{
		er_puts("Illegal number: ");
		er_puts(exstr);
		put_error('\n');
		return (2);
	}
	return (0);
}