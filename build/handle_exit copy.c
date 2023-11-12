#include "main.h"
#include <string.h>
#include <stdlib.h>
/**
 * handle_exit - Handle 'exit' command, terminating with optional status.
 *
 * @cmd_argv: Array of strings with command and arguments.
 * @line_buffer: Pointer to input command line buffer.
 *
 * Description:
 *   Checks if the command is 'exit'. Exits the program with an optional
 *   status from command arguments. Frees the line_buffer before exit.
 *
 * Parameters:
 *   - cmd_argv: Array of strings containing the command and arguments.
 *   - line_buffer: Pointer to the buffer with the input command line.
 *
 * Note:
 *   Exit status is 0 if no argument is provided.
 *
 * Example:
 *   Exit with custom status: `exit 42`
 *   Exit with default status (0): `exit`
 */
void handle_exit(char **cmd_argv, char *line_buffer)
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
