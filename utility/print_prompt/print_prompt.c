#include "main.h"

void print_prompt()
{
    if (isatty(STDIN_FILENO))
    {
        /* code */
        printf("$ ");
    }

}