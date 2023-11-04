#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    size_t read;

    printf("Enter a line of text (Ctrl+D to end):\n");
    

    while (read = getline(&line_buffer, &line_buffer_size, stdin) != -1)
    {
        printf("Your line: %s\n", line_buffer);
    }
    
    free(line_buffer);
    return 0;
}
