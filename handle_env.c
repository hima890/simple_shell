#include "main.h"
/**
 * handle_env - Prints the environment
 * variables to the standard output.
 *
 * @env: An array of strings
 * representing environment variables.
 *
 * Description:
 * This function takes a null-terminated array of strings representing
 * environment variables and prints each variable followed by a newline.
 * The input array is assumed to be terminated with a NULL pointer.
 *
 * Return: nothing function is of type void.
 */
void handle_env(char **env)
{
	unsigned int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}