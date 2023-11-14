<<<<<<< HEAD
#include "main.h"
/**
 * f_pt - Find the abolute pt of a command in the system pt.
 * @cn: Name of the command to find.
 * @ab: Buffer for the command's abolute pt.
 * @is: Flag for interactive shell mode.
 * @er: Pointer to an error indicator.
 * @av: Array of command-line arguments.
 * @env: Array of environment variables.
 * Return: abolute pt of the command on success, NULL on failure.
*/
char *f_pt(char *cn, char *ab, int is, int *er, char *const *av[], char **env)
{
	char *pt = setup_environment(env);

	return (fc(cn, ab, is, er, av, pt));
}
