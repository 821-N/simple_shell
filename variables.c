#include "shell.h"

/* Notes about variable lists (VarList):
 *  variables are stored in linked lists.
 *
 *  The first item is special. (& should be statically allocated)
 *  .length: number of "real" items in the list
 *  .next: pointer to first "real" item (or NULL)
 *
 *  Every other node stores a variable and is malloc'd.
 *  .next: points to the next item (or NULL, for the last item)
 *  .name: name of the variable (malloc'd string)
 *  .value: value of the variable (malloc'd string)
 */

int _strcmp(char *s1, char *s2)
{
	for (; *s1 == *s2 && *s1; s1++, s2++)
		;
	return (*s1 - *s2);
}

/**
 * free_list - free all data in a variable list
 * @var_list: head of list
 *  The head node is not freed, and its length value is set to 0
 *  THIS FUNCTION MUST BE CALLED BEFORE EXITING!!!
 */
void free_list(VarList *var_list)
{
	VarList *curr = var_list->next, *next;

	var_list->length = 0;
	while(curr)
	{
		next = curr->next;
		free(curr->name);
		free(curr->value);
		free(curr);
		curr = next;
	}
}

/**
 * get_variable - search for an item in a var list
 * @var_list: head of list to search
 * @name: name of variable to search for
 * Return: pointer to variable item (NOT .value string), or NULL
 */
VarList *get_variable(VarList *var_list, char *name)
{
	while (var_list = var_list->next)
	{
		if (_strcmp(var_list->name, name) == 0)
			return (var_list);
	}
	return (NULL);
}

/**
 * remove_variable - remove a variable from a var list
 * @var_list: head of list
 * @name: name of variable to remove
 * Return: 1 if variable was removed, 0 if var not found
 */
int remove_variable(VarList *var_list, char *name)
{
	VarList *prev = var_list, *curr;

	while (curr = prev->next)
	{
		if (_strcmp(curr->name, name) == 0)
		{
			prev->next = curr->next;
			free(curr);
			var_list->length--;
			return (1);
		}
		prev = curr->next;
	}
	return (0);
}

/**
 * set_variable - set or add variable to var list
 * @var_list: head
 * @name: name of var (should be malloc'd)
 * @value: value of var (should be malloc'd)
 *  If variable is in list, its value is replaced with @value.
 *  Otherwise, a new item is added to the start (after head),
 *  and var_list->length is updated.
 */
void set_variable(VarList *var_list, char *name, char *value)
{
	VarList *item = get_variable(var_list, name);

	if (item) /* if variable already exists: */
	{
		/* replace old value */
		free(item->value);
		item->value = value;
	}
	else /* otherwise create new variable: */
	{
		/* create new linked list node */
		item = malloc(sizeof(VarList));
		item->name = name;
		item->value = value;
		/* insert into list, after head */
		item->next = var_list->next;
		var_list->next = item;
		var_list->length++;
	}
}
