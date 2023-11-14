#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * tokenize_input - Tokenize the input line into command arguments.
 * @line_buffer: Pointer to the buffer with the input command line.
 * @cmd_argv: Array of strings to store the command and arguments.
 * @arc: Pointer to the argument count variable.
 * @max: Maximum number of arguments allowed.
 *
 * Description:
 *   Tokenizes the input line using space as a delimiter. Allocates memory for
 *   each token using strdup and populates the cmd_argv array with individual
 *   tokens. Updates the arc variable with the count of arguments.
 *   Null-terminates the argument array.
 *
 * Return:
 *   No explicit return value.
 *
 * Note:
 *   The function frees the line_buffer if no command is provided.
 *
 * Example:
 *   Input: "ls -l"
 *   Output: cmd_argv = {"ls", "-l", NULL}, arc = 2
 */
void tokenize_input(char *line_buffer, char **cmd_argv, int *arc, int max)
{
	char *token = strtok(line_buffer, " ");

	while ((token != NULL) && (*arc < max))
	{
		if (strcmp(token, "") != 0)
		{
			cmd_argv[*arc] = strdup(token);
			if (cmd_argv[*arc] == NULL)
			{
				fprintf(stderr, "Error: Memory allocation failed\n");
				exit(EXIT_FAILURE);
			}
			(*arc)++;
		}
		token = strtok(NULL, " ");
	}

	cmd_argv[*arc] = NULL; /* Null-terminate the argument array */
}
