#include "main.h"
/**
 * find_command_path - Find the absolute path of a command in the system PATH.
 * @cmd_name: Name of the command to find.
 * @absolute_path: Buffer for the command's absolute path.
 * @cmd_argv: Command and arguments as an array of strings.
 * @is_interactive: Flag for interactive shell mode.
 * @error: Pointer to an error indicator.
 * @argv: Array of command-line arguments.
 * Return: Absolute path of the command on success, NULL on failure.
 */
char *find_command_path(char *cmd_name, char *absolute_path, char **cmd_argv, int is_interactive, int *error, char *const *argv)
{
	char *path = getenv("PATH");

	if (command_exists(cmd_name) && path)
		strncpy(absolute_path, cmd_name, PATH_MAX);
	else
	{
		char *path_copy, *path_token;
		const char *delim_2 = ":";
		int command_found = 0;

		if (!path)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], 1, cmd_name);
			return NULL;
		}

		path_copy = strdup(path);

		for (path_token = strtok(path_copy, delim_2); path_token; path_token = strtok(NULL, delim_2))
		{
			DIR *command_dir = opendir(path_token);
			if (command_dir)
			{
				struct dirent *ent;
				while ((ent = readdir(command_dir)) != NULL)
					if (ent->d_type == DT_REG && strcmp(ent->d_name, cmd_name) == 0)
					{
						snprintf(absolute_path, PATH_MAX, "%s/%s", path_token, ent->d_name);
						command_found = 1;
						break;
					}
				closedir(command_dir);
			}
			else
				perror(cmd_argv[0]);

			if (command_found)
				break;
		}

		free(path_copy);

		if (!command_found)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], 1, cmd_name);
			if (!is_interactive)
				*error = 1;
			return NULL;
		}
	}

	return absolute_path;
}
