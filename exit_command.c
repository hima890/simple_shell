#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * isNumeric - Check if a string is a numeric value.
 * @str: The string to check.
 * Return: 1 if numeric, 0 otherwise.
 */
int isNumeric(const char *str)
{
	char *endptr;

	strtol(str, &endptr, 10);
	return (*endptr == '\0');
}

/**
 * exit_command - Execute the 'exit' command, handling special cases.
 *
 * @cv: Array of strings with command and arguments.
 * @lb: A string holding the input.
 * @error: The error indicator.
 * @arc: The number of arguments.
 * @argv: Array of command-line arguments.
 */
void exit_command(char **cv, char *lb, int error, int arc, char *const *argv)
{
	int es = 0;
	

	if (strcmp(cv[0], "exit") == 0)
	{
		if (cv[1] != NULL)
		{
			if (!isNumeric(cv[1]))
			{
				fprintf(stderr, "%s: %d: exit: Illegal number: %s\n", argv[0], 1, cv[1]);
				es = 2;
			}
			else
			{
				es = atoi(cv[1]);
			}

			if (es < 0)
			{
				fprintf(stderr, "%s: %d: exit: Illegal number: %d\n", argv[0], 1, es);
				es = 2;
			}
		}
		if (error == 2)
		{
			free_resources(lb, cv, arc);
			exit(error);
		}

		free_resources(lb, cv, arc);
		exit(es);
	}
}