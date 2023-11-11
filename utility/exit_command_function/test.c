#include "main.h"
#include <stdio.h>

/**
 * main - Test cases for the execute_command function.
 *
 * Return: Always 0.
 */
int main(void)
{
	/* Test case 1: "exit" command with status */
	char *cmd_argv1[] = {"exit", "42", NULL};

	/* Test case 2: "exit" command without status */
	char *cmd_argv2[] = {"exit", NULL};

	printf("Test Case 1:\n");
	printf("Input: %s\n", cmd_argv1[0]);
	exit_command(cmd_argv1);
	/* This won't be reached if the exit is successful */

	printf("Test Case 2:\n");
	printf("Input: %s\n", cmd_argv2[0]);
	exit_command(cmd_argv2);

	return (0);
}
