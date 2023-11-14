#include "main.h"
#include <stdlib.h>
#include <string.h>
/**
 * exit_command - Execute a command, handling special cases.
 *
 * @cmd_argv: Array of strings with command and arguments.
 * @line_buffer: A string holding the input
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
void exit_command(char **cmd_argv, char *line_buffer, int error, int arc)
{
	if (strcmp(cmd_argv[0], "exit") == 0)
	{
		int exit_status = 0;
		int i;

		if (cmd_argv[1] != NULL)
		{
			exit_status = atoi(cmd_argv[1]);
			free(line_buffer);
			for (i = 0; i < arc; i++)
			{
				free(cmd_argv[i]);
			}
			exit(exit_status);
		}
		else if (error == 2)
		{
			free(line_buffer);
			for (i = 0; i < arc; i++)
			{
				free(cmd_argv[i]);
			}
			exit(error);
		}
		free(line_buffer);
		for (i = 0; i < arc; i++)
		{
			free(cmd_argv[i]);
		}
		exit(exit_status);

	}
}
