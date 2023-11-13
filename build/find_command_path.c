#include "main.h"

/**
 * find - Find the command in a specific directory.
 * @cmd: Name of the command to find.
 * @path: Directory to search for the command.
 * @abs: Buffer for the command's absolute path.
 * Return: 1 if found, 0 otherwise.
 */
static int find(char *cmd, char *path, char *abs)
{
	DIR *command_dir = opendir(path);

	if (command_dir)
	{
		struct dirent *ent;

		while ((ent = readdir(command_dir)) != NULL)
		{
			if (ent->d_type == DT_REG && strcmp(ent->d_name, cmd) == 0)
			{
				snprintf(abs, PATH_MAX, "%s/%s", path, ent->d_name);
				closedir(command_dir);
				return (1);
			}
		}
		closedir(command_dir);
	}
	return (0);
}

/**
 * search_directories - Search for the command in the directories.
 * @cmd: Name of the command to find.
 * @pc: Copy of the system PATH.
 * @abs: Buffer for the command's absolute path.
 * Return: 1 if found, 0 otherwise.
 */
static int search_directories(char *cmd, char *pc, char *abs)
{
	const char *delim_2 = ":";
	char *pk;

	for (pk = strtok(pc, delim_2); pk; pk = strtok(NULL, delim_2))
	{
		if (find(cmd, pk, abs))
			return (1);
	}

	return (0);
}

/**
 * handel_cnf - Handle case when the command is not found.
 * @cmd: Name of the command.
 * @is: Flag for interactive shell mode.
 * @er: Pointer to an error indicator.
 * @argv: Array of command-line arguments.
 * Return: NULL.
 */
static char *handel_cnf(char *cmd, int is, int *er, char *const *argv)
{
	fprintf(stderr, "%s: %d: %s: not found\n", argv[0], 1, cmd);

	if (!is)
		*er = 1;

	return (NULL);
}

/**
 * f_path - Find the absolute path of a command in the system PATH.
 * @cmd: Name of the command to find.
 * @abs: Buffer for the command's absolute path.
 * @is: Flag for interactive shell mode.
 * @er: Pointer to an error indicator.
 * @argv: Array of command-line arguments.
 * Return: Absolute path of the command on success, NULL on failure.
 */
char *f_path(char *cmd, char *abs, int is, int *er, char *const *argv)
{
	char *path = getenv("PATH");
	char *pc;
	int command_found;

	if (command_exists(cmd) && path)
	{
		strncpy(abs, cmd, PATH_MAX);
	}
	else
	{
		if (!path)
			return (handel_cnf(cmd, is, er, argv));

		pc = strdup(path);
		command_found = search_directories(cmd, pc, abs);

		free(pc);

		if (!command_found)
			return (handel_cnf(cmd, is, er, argv));
	}

	return (abs);
}
