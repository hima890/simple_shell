#include "main.h"
/**
 * find_command_path - Searches for the absolute path
 * of a given command.
 * @cmd_name: The name of the command to find the path for.
 * @absolute_path: A buffer to store the absolute path of the command.
 * @env_path: The value of the PATH environment variable to search for the command.
 * Return:A dynamically allocated string containing the absolute path to the command,
 *         or NULL if the command is not found or an error occurs.
 */
char *find_command_path(const char *cmd_name, char *absolute_path, const char *env_path)
{
	if (command_exists(cmd_name))
	{
		strncpy(absolute_path, cmd_name, PATH_MAX);
	}
	else
	{
		if (env_path == NULL)
		{
			perror("find_command_path");
			return (NULL);
		}
		char *path_copy = strdup(env_path);
		int command_found_flag = 0;
		const char *delim_2 = ":";
		char *path_token = strtok(path_copy, delim_2);

		while (path_token != NULL)
		{
			DIR *command_dir = opendir(path_token);
			if (command_dir)
			{
				struct dirent *ent;
				while ((ent = readdir(command_dir)) != NULL)
				{
					if (ent->d_type == DT_REG && strcmp(ent->d_name, cmd_name) == 0)
					{
						snprintf(absolute_path, PATH_MAX, "%s/%s", path_token, ent->d_name);
						command_found_flag = 1;
						break;
					}
				}
				closedir(command_dir);
			}
			else
			{
				perror("find_command_path");
			}

			path_token = strtok(NULL, delim_2);

			if (command_found_flag == 1)
			{
				break;
			}
		}
		free(path_copy);
		if (command_found_flag == 0)
		{
			fprintf(stderr, "find_command_path: %d: %s: not found\n", __LINE__, cmd_name);
			return (NULL);
		}
	}
	char *result = strdup(absolute_path);
	return (result);
}