#include "main.h"
#include <stdlib.h>
#include <string.h>


int isNumeric(const char *str)
{
    char *endptr;

    strtol(str, &endptr, 10);
    return (*endptr == '\0');
}


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
void exit_command(char **cmd_argv, char *line_buffer, int error, int arc, char *const *argv)
{
    int exit_status = 0;
    int i;

    if (strcmp(cmd_argv[0], "exit") == 0)
    {
        if (cmd_argv[1] != NULL)
        {
            if (!isNumeric(cmd_argv[1]))
            {
                fprintf(stderr, "%s: %d: exit: Illegal number: %s\n", argv[0], 1, cmd_argv[1]);
                exit_status = 2;
            }
            else
            {
                exit_status = atoi(cmd_argv[1]);
            }

            if (exit_status < 0)
            {
                fprintf(stderr, "%s: %d: exit: Illegal number: %d\n", argv[0], 1, exit_status);
                exit_status = 2;
            }
        }

		if (error == 2)
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
