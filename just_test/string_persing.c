#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char string[] = "My name is - ibrahim hanafi - my number is : 0116897470";
    const char *delim = "-"; // Delimiter characters are ',' and '-'
    char *token = strtok(string, delim);

    while (token != NULL)
    {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }
    
    return 0;
}
