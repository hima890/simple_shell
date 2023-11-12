#include "main.h"
/**
 * find_command_path - Searches for the absolute path of a given command.
 * @cmd_name: The name of the command to find the path for.
 * @absolute_path: A buffer to store the absolute path of the command.
 * @env_path: The value of the PATH environment variable to search for the command.
 * Return: A dynamically allocated string containing the absolute path to the command,
 *         or NULL if the command is not found or an error occurs.
 */
char* find_command_path(const char *cmd_name, char *absolute_path, const char *env_path)
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
            return NULL;
        }

        char *path_copy = strdup(env_path);
        const char *delim = ":";
        char *path_token = strtok(path_copy, delim);
        int command_found_flag = 0;

        while (path_token != NULL)
        {
            if (search_in_directory(cmd_name, path_token, absolute_path))
            {
                command_found_flag = 1;
                break;
            }

            path_token = strtok(NULL, delim);
        }

        free(path_copy);

        if (command_found_flag == 0)
        {
            fprintf(stderr, "find_command_path: %d: %s: not found\n", __LINE__, cmd_name);
            return NULL;
        }
    }

    return strdup(absolute_path);
}