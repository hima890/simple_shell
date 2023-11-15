#include "main.h"
/**
 * print_prompt - Prints a command prompt, represented
 * by the '$' symbol, to the standard output (stdout).
 *
 * The prompt is displayed only if the program is being
 * run in an interactive terminal environment.
 *
 * It checks whether the standard input (stdin) is
 * connected to a terminal using the isatty function.
 *
 * Return: nothing function is of type void.
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		/* code */
		printf("$ ");
	}
}