#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * my_strdup - Custom implementation of strdup.
 *
 * @str: The input string to duplicate.
 * Return: A pointer to the duplicated string. Must be freed by the caller.
*/
char *my_strdup(const char *str)
{
size_t len = strlen(str) + 1;
char *dup_str = malloc(len);
if (dup_str != NULL)
{
memcpy(dup_str, str, len);
}
return (dup_str);
}


/**
 * main -  Handles the 'exit' command, exiting the
 *  program with a specified status.
 *
 * @param cmd_argv The command arguments.
 * @param line_buffer The input line buffer.
 * Return: 0
*/

int main(void)
{
/* Test case 1: 'exit' command with no arguments */
char *cmd_argv1[] = {"exit", NULL};
char *line_buffer1 = my_strdup("exit");
handle_exit(cmd_argv1, line_buffer1);
printf("Test case 1 failed\n");
free(line_buffer1);
return (0);
}
