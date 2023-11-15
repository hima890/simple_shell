#include "main.h"
/**
 * free_resources - Free allocated resources.
 *
 * @lb: A string holding the input.
 * @cv: Array of strings with command and arguments.
 * @arc: The number of arguments.
 * Return:nothing function is of type void.
 */
void free_resources(char *lb, char **cv, int arc)
{
    int i;
    if (lb != NULL)
    {
        free(lb);
    }
    if (cv != NULL)
    {
        for (i = 0; i < arc; ++i)
        {
            if (cv[i] != NULL)
            {
                free(cv[i]);
            }
        }

        
        free(cv);
    }
}
