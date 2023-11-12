#include "main.h"

/**
 * search_in_directory - Searches for the given command in a specific directory.
 * @cmd_name: The name of the command to find.
 * @directory: The directory to search for the command.
 * @absolute_path: A buffer to store the absolute path of the command.
 * Return: 1 if the command is found, 0 otherwise.
 */

static int search_in_directory(const char *cmd_name, const char *directory, char *absolute_path)
{
    DIR *command_dir = opendir(directory);
    if (!command_dir)
    {
        perror("search_in_directory");
        return 0;
    }

    struct dirent *ent;
    while ((ent = readdir(command_dir)) != NULL)
    {
        if (ent->d_type == DT_REG && strcmp(ent->d_name, cmd_name) == 0)
        {
            snprintf(absolute_path, PATH_MAX, "%s/%s", directory, ent->d_name);
            closedir(command_dir);
            return 1;
        }
    }

    closedir(command_dir);
    return 0;
}
