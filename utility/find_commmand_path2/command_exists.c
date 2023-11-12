#include "main.h"
/**
 * command_exists - a funtion to check if a command exists
 * @cmd_name: command name
 * Return: 0 || 1 depending on the case.
*/
int command_exists(char *cmd_name)
{
    return (access(cmd_name, X_OK) == 0);
}
