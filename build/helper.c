#include "main.h"
/**
 * find - Search for a command in a specific directory.
 * @cn: Name of the command to find.
 * @pt: Path of the directory to search.
 * @ab: Buffer to store the absolute path of the command.
 * Return: 1 if the command is found, 0 otherwise.
*/
int find(char *cn, char *pt, char *ab)
{
	DIR *command_dir = opendir(pt);

	if (command_dir)
	{
		struct dirent *ent;

		while ((ent = readdir(command_dir)) != NULL)
		{
			if (ent->d_type == DT_REG && strcmp(ent->d_name, cn) == 0)
			{
				snprintf(ab, pt_MAX, "%s/%s", pt, ent->d_name);
				closedir(command_dir);
				return (1);
			}
		}
		closedir(command_dir);
	}
	return (0);
}
/**
 * search_directories - Search for a command in multiple directories.
 * @cn: Name of the command to find.
 * @pc: Colon-separated paths to search.
 * @ab: Buffer to store the absolute path of the command.
 * Return: 1 if the command is found, 0 otherwise.
*/

int search_directories(char *cn, char *pc, char *ab)
{
	const char *delim_2 = ":";
	char *pk;

	for (pk = strtok(pc, delim_2); pk; pk = strtok(NULL, delim_2))
	{
		if (find(cn, pk, ab))
		{
			return (1);
		}
	}

	return (0);
}

/**
 * handle_cnf - Handle the case when a command is not found.
 * @cn: Name of the command that was not found.
 * @is: Flag for interactive shell mode.
 * @er: Pointer to an error indicator.
 * @argv: Array of command-line arguments.
 * Return: NULL.
*/
char *handle_cnf(char *cn, int is, int *er, char *const argv[])
{
	fprintf(stderr, "%s: %d: %s: not found\n", argv[0], 1, cn);
	if (!is)
	{
		*er = 1;
	}

	return (NULL);
}

/**
 * setup_environment - Set up the environment for command search.
 * @env: Array of environment variables.
 * Return: The pt variable.
 */
char *setup_environment(char **env)
{
	char *pt = getenv("PATH");
	char *new = getenv("PATH1");
	unsigned int i = 0;

	if (!pt)
	{
		setenv("PATH", DEFAULT_pt, 1);
		pt = getenv("PATH1");
	}

	if (new)
	{
		pt = NULL;
	}

	while (env[i] != NULL)
	{
		i++;
	}

	if (i <= 2)
	{
		pt = NULL;
	}

	return (pt);
}

/**
 * fc - Search for the abolute pt of a command.
 * @cn: Name of the command to find.
 * @ab: Buffer for the command's abolute pt.
 * @is: Flag for interactive shell mode.
 * @er: Pointer to an error indicator.
 * @argv: Array of command-line arguments.
 * @pt: The pt variable.
 * Return: abolute pt of the command on success, NULL on failure.
 */
char *fc(char *cn, char *ab, int is, int *er, char *const *argv, char *pt)
{
	int command_found;
	char *pc;

	if (command_exists(cn) && pt)
	{
		strncpy(ab, cn, pt_MAX);
	}

	if (strchr(cn, '/') != NULL)
	{
		strncpy(ab, cn, pt_MAX);
	}
	else
	{
		if (!pt)
		{
			return (handle_cnf(cn, is, er, argv));
		}

		pc = strdup(pt);
		command_found = search_directories(cn, pc, ab);

		free(pc);

		if (!command_found)
		{
			return (handle_cnf(cn, is, er, argv));
		}
	}

	return (ab);
}
