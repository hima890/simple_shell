#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_getenv(const char *name);

int main(int argc, char const *argv[])
{
    char *query;
    query = _getenv("QT_QPA_PLATFORMTHEME");
    printf("%s \n", query);
    return 0;
}

char *_getenv(const char *name)
{
    extern char **environ;
    int i = 0;
    for (i; environ[i] != NULL; i++)
    {
        if (strcmp(environ[i], name) != 0)
        {
            return (environ[i]);
        }
        
    }
}