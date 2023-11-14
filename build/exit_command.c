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
 * @ca: Array of strings with command and arguments.
 * @lb: A string holding the input.
 * @error: The error indicator.
 * @arc: The number of arguments.
 * @argv: Array of command-line arguments.
 */
void exit_command(char **ca, char *lb, int error, int arc, char *const *argv)
{
	int ext_st = 0;

	if (strcmp(ca[0], "exit") == 0)
	{
		if (ca[1] != NULL)
		{
			if (!isNumeric(ca[1]))
			{
				fprintf(stderr, "%s: %d: exit: Illegal number: %s\n", argv[0], 1, ca[1]);
				ext_st = 2;
			}
			else
			{
				ext_st = atoi(ca[1]);
			}

			if (ext_st < 0)
			{
				fprintf(stderr, "%s: %d: exit: Illegal number: %d\n", argv[0], 1, ext_st);
				ext_st = 2;
			}
		}

		if (error == 2)
		{
			free_resources(lb, ca, arc);
			exit(error);
		}

		free_resources(lb, ca, arc);
		exit(ext_st);
	}
}


/**
 * free_resources - Free memory.
 *
 * @ca: Array of strings with command and arguments.
 * @lb: A string holding the input.
 * @arc: The number of arguments.
 */
void free_resources(char *lb, char **ca, int arc)
{
	int i;

	for (i = 0; i < arc; i++)
	{
		free(ca[i]);
	}
	free(lb);
}
