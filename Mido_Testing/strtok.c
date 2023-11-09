#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char str[] = "ls -lab";
    char* piece = strtok(str, " ");

    while (piece != NULL)
    {
        printf("%s\n",piece);
        piece = strtok(NULL, " ");
    }
    
   
    return (0);
}
