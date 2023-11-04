#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (int i = 0; argv[i] != NULL; i++)
    {
        printf("ARG [%d]: %s\n", i, argv[i]);
    }
    
    return 0;
}
