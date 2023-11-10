#include <stdio.h>
#include "main.h"
/**
 * main - Entry point of the program to test command_exists function.
 *
 * Description:
 *   This function tests the command_exists function by
 *  checking the existence and executability
 *   of two commands: an existing command ("/bin/ls") and
 *  a non-existing command ("nonexistentcommand").
 *   It prints a message indicating whether each command
 *  exists and is executable or not.
 *
 * Return:
 *   Always returns 0, indicating successful execution of the program.
*/

int main(void)
{

/* Test with existing command */
char *existing_command = "/bin/ls";
/* Test with non-existing command */
char *non_existing_command = "nonexistentcommand";

if (command_exists(existing_command) == 0)
{
printf("%s exists and is executable.\n", existing_command);
}
else
{
printf("%s does not exist or is not executable.\n", existing_command);
}

if (command_exists(non_existing_command) == 0)
{
printf("%s exists and is executable.\n", non_existing_command);
}
else
{
printf("%s does not exist or is not executable.\n", non_existing_command);
}

return (0);
}
