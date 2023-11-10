#include "main.h"
#include <unistd.h>
/**
 * command_exists - Check if a command exists in the system's PATH.
 *
 * @cmd_name: The name of the command to check for existence.
 *
 * Description:
 *   This function checks if a given command exists in the
 *  system's PATH. It uses the access function
 *   to verify if the command is executable. If the command
 *  is found and executable, the function
 *   returns 0; otherwise, it returns -1.
 *
 * Return:
 *   0 if the command exists and is executable.
 *  -1 if the command does not exist or is not executable.
*/

int command_exists(char *cmd_name)
{

int command_status = access(cmd_name, X_OK);
return ((command_status == 0) ? 0 : -1);

}
