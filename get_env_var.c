#include <stdlib.h>

char *get_env_var(char **env, char *name)
{
	int i, j;
	char *item;

	for (j = 0; env[j] != NULL; j++)
	{
		item = env[j];
		for (i = 0; item[i] == name[i]; i++)
		{
		}
		if(item[i] == '=' && name[i] == '\0')
			return (&item[i + 1]);
	}
	return (NULL);
}
