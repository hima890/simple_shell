#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_ARGS 100
/**
 * main - Test cases for the tokenize_input function.
 * Return: Always 0.
*/
int main(void)
{
	
	/* Test case 1: Valid input with multiple tokens */
	char *line_buffer = "ls";
	char *cmd_argv1[MAX_ARGS];
	int argc1 = 0;
	/* Test case 2: Empty input */
	char *line_buffer_2 = "";
	char *cmd_argv2[MAX_ARGS];
	int argc2 = 0;
	int i;

	tokenize_input(line_buffer, cmd_argv1, &argc1, MAX_ARGS);
	printf("Test Case 1:\n");
	printf("Input: %s\n", line_buffer);
	printf("Result:\n");
	for (i = 0; i < argc1; i++)
	{
		printf("Token %d: %s\n", i + 1, cmd_argv1[i]);
	}
	printf("\n");
	for (i = 0; i < argc1; i++)
	{
		free(cmd_argv1[i]);
	}


	tokenize_input(line_buffer_2, cmd_argv2, &argc2, MAX_ARGS);
	printf("Test Case 2:\n");
	printf("Input: %s\n", line_buffer_2);
	printf("Result:\n");
	for (i = 0; i < argc2; i++)
	{
		printf("Token %d: %s\n", i + 1, cmd_argv2[i]);
	}
	printf("\n");
	for (i = 0; i < argc2; i++)
	{
		free(cmd_argv2[i]);
	}
	return (0);
}
