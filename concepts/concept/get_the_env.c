#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    extern char **environ;
    int i = 0;
    for (i; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
    return 0;
}
