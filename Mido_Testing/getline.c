#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t n = 10;

    char *buf = malloc(sizeof(char) * n); /*we can do null as well it can dynamicly allocate memory*/

    printf("$ ");

    getline(&buf, &n, stdin);
    printf("the input is : %s and the buffer size is : %ld\n", buf, n);

    free(buf);

    return (0);
}