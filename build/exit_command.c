#include "main.h"
#include <stdlib.h>
#include <string.h>
/**
 * exit_command - Execute a command, handling special cases.
 *
 * @cmd_argv: Array of strings with command and arguments.
 *
 * Description:
 *   Checks if the command is 'exit'. If true, it terminates the program
 *   with an optional status obtained from command arguments.
 *
 * Parameters:
 *   - cmd_argv: Array of strings containing the command and arguments.
 *
 * Note:
 *   Exit status is 0 if no argument is provided.
 *
 * Example:
 *   Execute 'exit' command with custom status: `exit 42`
 */
void exit_command(char **cmd_argv, char *line_buffer)
{
	if (strcmp(cmd_argv[0], "exit") == 0)
	{
		int exit_status = 0;

		if (cmd_argv[1] != NULL)
		{
			exit_status = atoi(cmd_argv[1]);
		}

		free(line_buffer);
		exit(exit_status);
	}
}
